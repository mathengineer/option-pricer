#include "MarketData.h"
#include <iostream>

MarketData::MarketData() {}

MarketData::~MarketData()
{
    delete _riskFreeRatePtr;
}

double MarketData::getPrice(std::string ticker) const
{
    return _prices.at(ticker);
}

double MarketData::getVol(std::string ticker) const
{
    return _vols.at(ticker);
}

double MarketData::getRiskFreeRate() const
{
    return *_riskFreeRatePtr;
}

void MarketData::setRiskFreeRate(double riskFreeRate)
{
    *_riskFreeRatePtr = riskFreeRate;
}

const std::set<std::string>& MarketData::getRiskFactors() const
{
    return _riskFactors;
}

void MarketData::addRiskFactor(std::string ticker, double price, double vol)
{
    _riskFactors.insert(ticker);
    _prices[ticker] = price;
    _vols[ticker] = vol;
}

void MarketData::removeRiskFactor(std::string ticker)
{
    std::cout << "Remove " << ticker << " from the market data." << std::endl;
    _riskFactors.erase(ticker);
    _prices.erase(ticker);
    _vols.erase(ticker);
}

void MarketData::print()
{
    std::cout << "Current market data:" << std::endl;
    std::cout << "Risk free rate: " << getRiskFreeRate() << std::endl;
    for (auto it=getRiskFactors().begin(); 
    it!=getRiskFactors().end(); ++it)
    {
        std::cout << *it << ": current price is " << getPrice(*it) 
        << " and vol is " << getVol(*it) << std::endl;
    }
    std::cout << std::endl;    
}

MarketData::MarketData(const MarketData &source)
{
    *_riskFreeRatePtr = *source._riskFreeRatePtr;
    for (auto it=source.getRiskFactors().begin(); 
    it!=source.getRiskFactors().end(); ++it)
    {
        addRiskFactor(*it, source.getPrice(*it), source.getVol(*it));
    }
}

MarketData &MarketData::operator=(const MarketData &source)
{
    if (this == &source) return *this;
    
    *_riskFreeRatePtr = *source._riskFreeRatePtr;
    for (auto it=source.getRiskFactors().begin(); 
    it!=source.getRiskFactors().end(); ++it)
    {
        addRiskFactor(*it, source.getPrice(*it), source.getVol(*it));
    }

    return *this;
}

MarketData::MarketData(MarketData &&source)
{
    _riskFreeRatePtr = source._riskFreeRatePtr;
    source._riskFreeRatePtr = nullptr;
    _vols = std::move(source._vols);
    _prices = std::move(source._prices);
    _riskFactors = std::move(source._riskFactors);
}

MarketData &MarketData::operator=(MarketData &&source)
{
    if (this == &source) 
    {
        return *this;
    }
    else
    {
        _riskFreeRatePtr = source._riskFreeRatePtr;
        source._riskFreeRatePtr = nullptr;
        _vols = std::move(source._vols);
        _prices = std::move(source._prices);
        _riskFactors = std::move(source._riskFactors);
        
        return *this;
    }
}