#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#include <string>
#include <unordered_map>
#include <set>

class MarketData
{
    public:
        // Expose the data but they should only be accessed through get, add and etc by other functions/classes
        // This exposure is just for the ease of implement move in rule of five
        double *_riskFreeRatePtr = new double{0.0}; // For the sake of having unmanaged dynamically allocated memory
        std::set<std::string> _riskFactors; 
        std::unordered_map<std::string, double> _vols;
        std::unordered_map<std::string, double> _prices;

        double getPrice(std::string ticker) const;
        double getVol(std::string ticker) const;
        double getRiskFreeRate() const;
        void setRiskFreeRate(double riskFreeRate);
        const std::set<std::string>& getRiskFactors() const;
        void addRiskFactor(std::string ticker, double price, double vol);
        void removeRiskFactor(std::string ticker);
        void print();

        MarketData();

        // Rule of five
        // Destructor
        ~MarketData();
        // Copy construct
        MarketData(const MarketData &source);
        // Copy assignment
        MarketData &operator=(const MarketData &source);
        // Move construct
        MarketData(MarketData &&source);
        // Move assignment
        MarketData &operator=(MarketData &&source);
};

#endif