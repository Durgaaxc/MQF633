#include <fstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Market.h"
#include "Pricer.h"
#include "EuropeanTrade.h"
#include "Bond.h"
#include "Swap.h"
#include "AmericanTrade.h"

using namespace std;

// Function to read content from a file
void readFromFile(const string& fileName, string& outPut) {
    string lineText;
    ifstream MyReadFile(fileName);
    while (getline(MyReadFile, lineText)) {
        outPut.append(lineText);
    }
    MyReadFile.close();
}

// Black-Scholes pricing function for European option
double BlackScholesEuropeanOptionPrice(double S, double K, double T, double r, double sigma, bool isCall) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    if (isCall) {
        return S * std::erfc(-d1 / std::sqrt(2)) / 2 - K * exp(-r * T) * std::erfc(-d2 / std::sqrt(2)) / 2;
    } else {
        return K * exp(-r * T) * std::erfc(d2 / std::sqrt(2)) / 2 - S * std::erfc(d1 / std::sqrt(2)) / 2;
    }
}

int main() {
    // Task 1: Create a market data object and update the market data from a text file
    std::time_t t = std::time(0);
    auto now_ = std::localtime(&t);
    Date valueDate(now_->tm_year + 1900, now_->tm_mon + 1, now_->tm_mday);

    Market mkt(valueDate);
    // Load data from file and update market object with data
    string marketData;
    readFromFile("market_data.txt", marketData);
    // Assume marketData contains properly formatted market information
    // Parsing and updating the market object with marketData can be implemented here

    // Task 2: Create a portfolio of bond, European option, and American option
    vector<Trade*> myPortfolio;
    myPortfolio.push_back(new Bond(Date(2024, 1, 1), Date(2034, 1, 1), 10000000, 103.5));
    myPortfolio.push_back(new EuropeanOption(Call, 100, Date(2024, 5, 1)));
    myPortfolio.push_back(new AmericanOption(Put, 100, Date(2024, 5, 1)));
    // Add more trades to meet the requirement of no less than 16 trades

    // Task 3: Create a pricer and price the portfolio, output the pricing result of each deal
    CRRBinomialTreePricer treePricer(10); // Correctly initialize a specific tree pricer
    for (auto trade : myPortfolio) {
        double pv = treePricer.Price(mkt, trade);
        // Log pv details out in a file
        ofstream resultFile("pricing_results.txt", ios::app);
        if (resultFile.is_open()) {
            resultFile << "Trade: " << trade->getType() << ", PV: " << pv << endl;
            resultFile.close();
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    // Task 4: Analyzing pricing result
    // a) Compare CRR binomial tree result for a European option vs Black model
    double S = 100, K = 100, T = 0.25, r = 0.04, sigma = 0.15;
    // Calculate the price using Black-Scholes model (assuming call option)
    double euroPriceBlack = BlackScholesEuropeanOptionPrice(S, K, T, r, sigma, true);
    // Now let's compare it with the price from the binomial tree
    double euroPriceCRR = treePricer.PriceEuropeanOption(S, K, T, r, sigma);
    cout << "European Option CRR Price: " << euroPriceCRR << ", Black Price: " << euroPriceBlack << endl;

    // b) Compare CRR binomial tree result for an American option vs European option
    // Let's get the price for the American option
    double amerPriceCRR = treePricer.PriceAmericanOption(S, K, T, r, sigma);
    cout << "American Option CRR Price: " << amerPriceCRR << ", European Option CRR Price: " << euroPriceCRR << endl;

    // Clean up dynamically allocated Trade objects
    for (auto trade : myPortfolio) {
        delete trade;
    }

    cout << "Project build successfully!" << endl;
    return 0;
}
