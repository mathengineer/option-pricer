# Simple option pricer
This is a simple option pricer to calculate the prices for all options within a portfolio. This is for Udacity C++ Nanodegree Capstone Project (Capstone Option 1 -- build the project of your choice).

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./option_pricer
```
The program will ask for the location of **portfolio** and **market** data. Sample data is include (portfolio and market under /data).
If the sample data is used (i.e. when the program asks for porfolio file name enter portfolio and when the program asks for market data file enter market), 
the following out put is expected:
```
Please provide portfolio filename (under data folder): portfolio
Read in portfolio data from ../data/portfolio
Please provide market date filename (under data folder): market
Read in market data from ../data/market
Current market data:
Risk free rate: 0.01
AAPL: current price is 285 and vol is 0.84
JPM: current price is 90 and vol is 0.81

Put market data into portfolio and validate the pricer under boundary case (zero rate and near zero vol):
Call opton on AAPL (strike is 285.00 and notional is 100.00) price = 0.00 when current stock price is 285.00 and zero vol and zero risk free rate.
Put opton on JPM (strike is 85.00 and notional is 200.00) price = 0.00 when current stock price is 90.00 and zero vol and zero risk free rate.

Price all options in the portfolio under current market condition(risk free rate is 0.01) :
Call opton on AAPL (strike is 285.00 and notional is 100.00) price = 6710.08 when current stock price is 285.00 and vol is 0.84
Put opton on JPM (strike is 85.00 and notional is 200.00) price = 2313.62 when current stock price is 90.00 and vol is 0.81
```

### Input file format
* **Portfolio** file: 
This file must contain inform for a portfolio of options. Each line represents an option. The information on each line must be as following (space in between):

stock_ticker option_type option_strike_price option_expiry notional

* **Market** data file:
This file must contain market data enough for market scenario generation and option pricing. First line is risk free rate and the following lines are stock vol like following (space in between):

risk_free_rate

stock1_ticker stock1_price stock1_vol

stock2_ticker stock2_price stock2_vol

## Class Structure
1. In Instruments.h: Instrument class is the base class, Option class is drived from the Instrument class. These classes are responsible to store option contract information and to price the option.
2. In MarketData.h: MarketData class is for handling market data such as risk free rate, stock price and vol.
3. In InputParser.h: namespace InputParser contains tools to read in a portfolio of options and market data.

## C++ Capstone Project Criteria Met

### All three criteria in Loops, Functions, I/O are satisfied
1. Function, control structure and etc: it is everywhere
2. Read data from file: InputParser.cpp
3. Accept user inputs: main.cpp

### All nine criteria in Object Oriented Programming are satisfied
1. In Instruments.h and Instruments.cpp, Option class inherits from Instrument class that meets different requirements expect the last one about Templates.
2. Template function used in RiskSimulator class in RiskEngine.h

### All criteria except the last one in Memory Management are satisfied
1. See Instruments.h and Instruments.cpp
