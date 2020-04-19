#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>

#include "InputParser.h"

void InputParser::readPortfolio(std::string filename, std::vector<Option> &portfolio)
{
    std::string line;
    std::string ticker;
    Option::OptionType optionType;
    double strike, expiry, notional;

    std::ifstream filestream(dataDirectory+filename);
    if (filestream.is_open())
    {
        std::cout << "Read in portfolio data from " << dataDirectory+filename << std::endl;
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            linestream >> ticker;
            std::string optionTypeString;
            linestream >> optionTypeString;
            if (optionTypeString=="call")
            {
                optionType = Option::call;
            }
            else if (optionTypeString=="put")
            {
                optionType = Option::put;
            }
            else
            {
                throw std::invalid_argument("Invalid option type!");
            }
            linestream >> strike >> expiry >> notional;
            portfolio.emplace_back(Option(ticker, optionType, strike, expiry, notional));
        }
    }
    else
    {
        throw std::runtime_error("Cannot open portfolio file!");
    }
    
}

void InputParser::readMarketData(std::string filename, MarketData &marketData)
{
    std::string line;
    std::string ticker;
    double riskFreeRate, stockPrice, vol;

    std::ifstream filestream(dataDirectory+filename);
    if (filestream.is_open())
    {
        std::cout << "Read in market data from " << dataDirectory+filename << std::endl;
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> riskFreeRate;
        marketData.setRiskFreeRate(riskFreeRate); 
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            linestream >> ticker;
            linestream >> stockPrice >> vol;
            marketData.addRiskFactor(ticker, stockPrice, vol);
        }
    }
    else
    {
        throw std::runtime_error("Cannot open portfolio file!");
    }
    
}