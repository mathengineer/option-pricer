#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>

#include "Instruments.h"
#include "MarketData.h"

namespace InputParser
{
    const std::string dataDirectory{"../data/"};

    void readPortfolio(std::string filename, std::vector<Option> &portfolio);
    void readMarketData(std::string filename, MarketData &marketData);
}

#endif