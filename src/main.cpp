#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "InputParser.h"
#include "Instruments.h"
#include "MarketData.h"

int main() 
{

    std::cout << "Please provide portfolio filename (under data folder): ";
    std::string portfolioFilename;
    std::cin >> portfolioFilename;
    std::vector<Option> portfolio;
    InputParser::readPortfolio(portfolioFilename, portfolio);

    std::cout << "Please provide market date filename (under data folder): ";
    std::string marketFilename;
    std::cin >> marketFilename;
    MarketData marketData;
    
    InputParser::readMarketData(marketFilename, marketData);
    marketData.print();
    
    // Load the market data and validate the pricing
    std::cout << "Put market data into portfolio and validate the pricer under boundary case (zero rate and near zero vol):"
    << std::endl;
    for (Option &option : portfolio)
    {
        option.setMarket(marketData);
        // Validate the input and the pricing
        std::cout << option.getTradeInfo() << " price = " 
        << std::setprecision(2) << std::fixed
        << option.calculatePV(0, marketData.getPrice(option.getUnderlyingName()), 0.000000001, 0.0) 
        << " when current stock price is " << marketData.getPrice(option.getUnderlyingName()) 
        << " and zero vol and zero risk free rate." << std::endl; 
    }
    std::cout << std::endl;

    std::cout << "Price all options in the portfolio under current market condition(risk free rate is " << marketData.getRiskFreeRate()
    << ") :" << std::endl;

    for (Option &option : portfolio)
    {
        std::cout << option.getTradeInfo() << " price = " 
        << std::setprecision(2) << std::fixed
        << option.calculatePV(0, marketData.getPrice(option.getUnderlyingName())) 
        << " when current stock price is " << marketData.getPrice(option.getUnderlyingName()) 
        << " and vol is " <<  marketData.getVol(option.getUnderlyingName())  << std::endl; 
    }

    return 0;
}