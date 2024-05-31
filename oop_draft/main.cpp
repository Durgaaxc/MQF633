#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>

#include "Market.h"
#include "Pricer.h"
#include "EuropeanTrade.h"
#include "Bond.h"
#include "Swap.h"
#include "AmericanTrade.h"
#include "Date.h"
#include "Option.h"



using namespace std;

void readFromFile(const string& fileName, string& outPut) {
    string lineText;
    ifstream MyReadFile(fileName);
    while (getline(MyReadFile, lineText)) {
        outPut.append(lineText + "\n");  // Ensure each line is separated by a newline
    }
    MyReadFile.close();
}

int main() {
    // Task 1: Create a market data object and update the market data from txt file
    std::time_t t = std::time(0);
    auto now_ = std::localtime(&t);
    Date valueDate(now_->tm_year + 1900, now_->tm_mon + 1, now_->tm_mday);

    Market mkt(valueDate);

    // Update interest rate curves
    string curveData;
    readFromFile("curve.txt", curveData);
    mkt.updateInterestRateCurves(curveData);

    // Update volatility curves
    string volData;
    readFromFile("vol.txt", volData);
    mkt.updateVolatilityCurves(volData);

    // Update bond prices
    string bondPriceData;
    readFromFile("bondprice.txt", bondPriceData);
    mkt.updateBondPrices(bondPriceData);

    // Update stock prices
    string stockPriceData;
    readFromFile("stockprice.txt", stockPriceData);
    mkt.updateStockPrices(stockPriceData);

    // Print the market data to verify updates
    mkt.Print();


    // Task 2: Create a portfolio of bond, swap, european option, american option
    // for each time, at least should have long / short, different tenor or expiry, different underlying
    // totally no less than 16 trades
    vector<Trade*> myPortfolio;

    // Trade 1: Long bond trade
    Trade* bondLong1 = new Bond(Date(2024, 1, 1), Date(2034, 1, 1), 10000000, 103.5);
    myPortfolio.push_back(bondLong1);

    // Trade 2: Short swap trade
    Trade* swapShort1 = new Swap(Date(2024, 1, 1), Date(2031, 1, 1), -8000000, 1.5, 0.05, 1);
    myPortfolio.push_back(swapShort1);

    // Trade 3: Long stock option trade
    Trade* stockOptionLong1 = new EuropeanOption(OptionType::Call, 300, Date(2027, 1, 1));
    myPortfolio.push_back(stockOptionLong1);

    // Trade 4: Short bond trade
    Trade* bondShort1 = new Bond(Date(2024, 1, 1), Date(2033, 1, 1), -5000000, 100.5);
    myPortfolio.push_back(bondShort1);

    // Trade 5: Long swap trade
    Trade* swapLong1 = new Swap(Date(2024, 1, 1), Date(2034, 1, 1), 12000000, 1.7, 0.05, 1);
    myPortfolio.push_back(swapLong1);

    // Trade 6: Short stock option trade
    Trade* stockOptionShort1 = new EuropeanOption(OptionType::Put, 250, Date(2026, 1, 1));
    myPortfolio.push_back(stockOptionShort1);

    // Add more trades to reach a total of at least 16 trades...
    // Trade 7: Long bond trade
    Trade* bondLong2 = new Bond(Date(2025, 1, 1), Date(2035, 1, 1), 15000000, 105.5);
    myPortfolio.push_back(bondLong2);

    // Trade 8: Short swap trade
    Trade* swapShort2 = new Swap(Date(2025, 1, 1), Date(2032, 1, 1), -10000000, 1.6, 0.05, 1);
    myPortfolio.push_back(swapShort2);

    // Trade 9: Long stock option trade
    Trade* stockOptionLong2 = new EuropeanOption(OptionType::Call, 400, Date(2028, 1, 1));
    myPortfolio.push_back(stockOptionLong2);

    // Trade 10: Short bond trade
    Trade* bondShort2 = new Bond(Date(2025, 1, 1), Date(2034, 1, 1), -8000000, 102.5);
    myPortfolio.push_back(bondShort2);

    // Trade 11: Long swap trade
    Trade* swapLong2 = new Swap(Date(2025, 1, 1), Date(2035, 1, 1), 18000000, 1.8, 0.05, 1);
    myPortfolio.push_back(swapLong2);

    // Trade 12: Short stock option trade
    Trade* stockOptionShort2 = new EuropeanOption(OptionType::Put, 300, Date(2027, 1, 1));
    myPortfolio.push_back(stockOptionShort2);

    // Trade 13: Long bond trade
    Trade* bondLong3 = new Bond(Date(2026, 1, 1), Date(2036, 1, 1), 20000000, 107.5);
    myPortfolio.push_back(bondLong3);

    // Trade 14: Short swap trade
    Trade* swapShort3 = new Swap(Date(2026, 1, 1), Date(2033, 1, 1), -15000000, 1.8, 0.05, 1);
    myPortfolio.push_back(swapShort3);

    // Trade 15: Long stock option trade
    Trade* stockOptionLong3 = new EuropeanOption(OptionType::Call, 500, Date(2029, 1, 1));
        myPortfolio.push_back(stockOptionLong3);

    // Trade 16: Short bond trade
    Trade* bondShort3 = new Bond(Date(2026, 1, 1), Date(2035, 1, 1), -10000000, 104.5);
    myPortfolio.push_back(bondShort3);

    // Trade 17: Long swap trade
    Trade* swapLong3 = new Swap(Date(2026, 1, 1), Date(2036, 1, 1), 22000000, 1.9, 0.05, 1);
    myPortfolio.push_back(swapLong3);

    // Task 3: Create a pricer and price the portfolio, output the pricing result of each deal
    Pricer* treePricer = new CRRBinomialTreePricer(10);
    ofstream outputFile("pricing_results.txt"); // Open a file to log pricing results

    // Task 3: Price each trade in the portfolio
    for (auto trade : myPortfolio) {
        double pv = treePricer->Price(mkt, trade);
        // Log pv details out in a file
        outputFile << "Trade: " << trade->getType() << ", PV: " << pv << endl;
    }

    outputFile.close(); // Close the output file

    // Task 4: Analyzing pricing results
    // a) Compare CRR binomial tree result for a European option vs Black-Scholes model
    // For simplicity, assume the Black-Scholes model implementation is available elsewhere
    // Let's say we have a function called BlackScholesPrice(Option* option, Market* market)

    // Get the European options from the portfolio
    vector<EuropeanOption*> europeanOptions;
    for (auto trade : myPortfolio) {
        if (auto europeanOption = dynamic_cast<EuropeanOption*>(trade)) {
            europeanOptions.push_back(europeanOption);
        }
    }

    // Compare pricing results
    for (auto europeanOption : europeanOptions) {
        double crrPrice = treePricer->Price(mkt, europeanOption);
        double blackScholesPrice = BlackScholesPrice(europeanOption, &mkt);

        cout << "European Option Comparison:" << endl;
        cout << "CRR Binomial Tree Price: " << crrPrice << endl;
        cout << "Black-Scholes Model Price: " << blackScholesPrice << endl;
    }

    // b) Compare CRR binomial tree result for an American option vs European option
    // Similar to part a), compare pricing results for American and European options
    vector<AmericanOption*> americanOptions;

    for (auto trade : myPortfolio) {
        if (auto americanOption = dynamic_cast<AmericanOption*>(trade)) {
            americanOptions.push_back(americanOption);
        }
    }

    // Compare pricing results
    for (auto americanOption : americanOptions) {
        double crrPriceAmerican = treePricer->Price(mkt, americanOption);

        cout << "American Option Pricing:" << endl;
        cout << "CRR Binomial Tree Price (American): " << crrPriceAmerican << endl;
    }
    
    // Final message
    cout << "Project build successfully!" << endl;
    return 0;
}

