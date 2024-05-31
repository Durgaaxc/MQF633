#include <fstream>
#include <ctime>
#include <chrono>
#include <iostream>
#include <sstream>

#include "Market.h"
#include "Date.h"
#include "Pricer.h"
#include "EuropeanTrade.h"
#include "Bond.h"
#include "Swap.h"
#include "AmericanTrade.h"
#include "Types.h"
#include "Trade.h"
#include "Pricer.h"


using namespace std;


void readFromFile(const string& fileName, string& outPut){
  string lineText;
  ifstream MyReadFile(fileName);
  while (getline (MyReadFile, lineText)) {
    outPut.append(lineText);
  }
  MyReadFile.close();
}

int main()
{
  //task 1, create an market data object, and update the market data from from txt file 
  
  std::time_t t = std::time(0);
  auto now_ = std::localtime(&t);
  Date valueDate;
  valueDate.year = now_->tm_year + 1900;
  valueDate.month = now_->tm_mon + 1;
  valueDate.day = now_->tm_mday;
  Market mkt1= Market(valueDate);
  mkt1.addBondPrice("SGD-GOV",102.5);
  mkt1.addBondPrice("USD-GOV",105.4);
  mkt1.addBondPrice("SGD-MAS-BILL",98);
  mkt1.addStockPrice("AAPL",652.0);
  mkt1.addStockPrice("SP500",5035.7);
  mkt1.addStockPrice("STI",3420);
  VolCurve volatility = VolCurve();
  RateCurve rate = RateCurve(); 
  std::vector<std::string> voltimeSteps = {"1M", "3M", "6M", "9M", "1Y", "2Y", "5Y", "10Y"};
  std::vector<std::string> ratetimeSteps = {"0M", "3M", "6M", "9M", "1Y", "2Y", "5Y", "10Y"};
  std::vector<double> volRates = {25.6,20.1,18.7,15.4,14.3,14.9,14.5,13.5};
  std::vector<double> Rates = {5.56,5.5,5.45,5.4,5.53,5.34,4.75,3.90};
  for (int i = 0; i < voltimeSteps.size(); i++) {
    // Parse time step into a date (assuming a way to convert from string to Date)
    Date voltenor = valueDate.addTimeStep(voltimeSteps.at(i));
    Date ratetenor = valueDate.addTimeStep(ratetimeSteps.at(i)); // Implement parseTimeStepToDate function
    volatility.addVol(voltenor, volRates.at(i));
    rate.addRate(ratetenor,Rates.at(i));
  };
  mkt1.addCurve("USD-SOFR",rate);
  mkt1.addVolCurve("Volatility",volatility);
  mkt1.Print();
}
 