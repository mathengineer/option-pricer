#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <sstream>

#include "MarketData.h"

// Base class for all financial derivatives
class Instrument
{
    public:
        Instrument() noexcept;
        virtual bool isExpired(double t) const = 0; // Check whether the option is expired at time t
        virtual double calculatePV(double t, double underlyingPrice) const = 0; // Used in NPV
        double NPV(double t, double underlyingPrice) const; // Calculate NPV of the instrument
        
    protected:
        bool _marketDataAvailable;             
};

// Equity European Option class
class Option : public Instrument
{
    public:
        enum OptionType {call, put};

        
        Option(std::string ticker, OptionType optionType, double strike, 
        double expiry, double notional);
        std::string getUnderlyingName() const;
        std::string getTradeInfo() const;
        void setMarket(MarketData &marketData);
        bool isExpired(double t) const;
        double calculatePV(double t, double stockPrice) const;
        double calculatePV(double t, double stockPrice, double vol, double riskFreeRate); // Overload to allow user to input vol for testing
        
    private:
        std::string _ticker;
        OptionType _type;
        double _strike;
        double _notional;
        double _riskFreeRate;
        double _vol;
        double _expiry; // Number of years from today to expiration date of the instrument
};

#endif