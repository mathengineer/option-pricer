#include <cmath>
#include <iomanip>
#include "Instruments.h"

Instrument::Instrument() noexcept : _marketDataAvailable(false) {}

double Instrument::NPV(double t, double underlyingPrice) const
{
    if (! _marketDataAvailable)
    {
        throw std::runtime_error("Market data is not available for pricing!");
    }

    if (isExpired(t))
    {
        return 0.0;
    }
    else
    {
        return calculatePV(t, underlyingPrice);
    }
}

Option::Option(std::string ticker, OptionType optionType, 
double strike, double expiry, double notional) : 
_ticker(ticker), _type(optionType), _strike(strike), 
_expiry(expiry), _notional(notional), Instrument() {}

std::string Option::getUnderlyingName() const
{
    return _ticker;
}

std::string Option::getTradeInfo() const
{
    std::ostringstream info; 
    info << ((_type==call) ? "Call" : "Put") << " opton on " 
    << _ticker << " (strike is " << std::setprecision(2) << std::fixed 
    << _strike << " and notional is " << _notional << ")";
    return info.str();
}

void Option::setMarket(MarketData &marketData)
{
    _riskFreeRate = marketData.getRiskFreeRate();
    _vol = marketData.getVol(getUnderlyingName());
    _marketDataAvailable = true;
}

bool Option::isExpired(double t) const
{
    return t >= _expiry;
}

double normalCDF(double x) // N(x)
{
    return std::erfc(-x/std::sqrt(2))/2;
}

double Option::calculatePV(double t, double stockPrice) const
{
    // Classical Black Scholes formula for option pricing assuming no dividend for the stock
    // See https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model
    const double d1 = 1 / (_vol * std::sqrt(_expiry-t)) * 
    (std::log(stockPrice/_strike) + (_riskFreeRate + std::pow(_vol, 2)/2) * (_expiry-t));
    const double d2 = d1 - _vol * std::sqrt(_expiry-t);
    if (_type == call)
    {
        return _notional * (normalCDF(d1) * stockPrice 
        - normalCDF(d2) * _strike * std::exp(-_riskFreeRate*(_expiry-t)));
    }
    else
    {
        return _notional * (normalCDF(-d2) * _strike * std::exp(-_riskFreeRate*(_expiry-t))
        - normalCDF(-d1) * stockPrice);
    }
}

double Option::calculatePV(double t, double stockPrice, double vol, double riskFreeRate)
{
    // Temporarily alter the _vol and _riskFreeRate for testing
    auto tempVol = _vol;
    auto tempRiskFreeRate = _riskFreeRate;
    _vol = vol;
    _riskFreeRate = riskFreeRate;
    auto pv = calculatePV(t, stockPrice);

    // Set _vol and _riskFreeRate back
    _vol = tempVol;
    _riskFreeRate = tempRiskFreeRate;
    return pv;
}