#include <fstream>
#include <ctime>
#include <chrono>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <ctime>
#include <cmath>

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
struct BONDSTOCK {
  std::string currencyPair;
  double rate;
};
struct Volt {
  std::string title;
  std::string timeStep;
  double value;
};

void readFromFile(const string& fileName, std::vector<BONDSTOCK>& exchangeRates){
  string lineText;
  ifstream MyReadFile(fileName);
  while (getline (MyReadFile, lineText)) {
    istringstream iss(lineText);
    string bondName;
    double price;
    iss >> bondName;
    if (bondName.back() == ':') bondName.pop_back();
    iss >> price;
    exchangeRates.push_back({bondName, price});
  }
  MyReadFile.close();
}

void readFromFilecurves(const string& fileName, std::vector<Volt>& Curves){
  string lineText;
  ifstream MyReadFile(fileName);
  std::string title;
  std::getline(MyReadFile, title);
  while (getline (MyReadFile, lineText)) {
    istringstream iss(lineText);
    std::string timeStep;
    double value;
    std::getline(iss, timeStep, ':');
    iss >> value;
    Curves.push_back({title,timeStep, value});
  }
  MyReadFile.close();
}
double norm_cdf(double x) {
    return 0.5 * erfc(-x *0.70710678118);
}

double BlackScholesPrice(double S, double K, double T, double r, double sigma, OptionType optType) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    
    if (optType == Call) {
        return S * norm_cdf(d1) - K * exp(-r * T) * norm_cdf(d2);
    } else {
        return K * exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
    }
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
  std::vector<BONDSTOCK> exchangeRates;
  std::vector<BONDSTOCK> stock;
  readFromFile("bondPrice.txt", exchangeRates);
  readFromFile("stockPrice.txt",stock);
  
  for (const BONDSTOCK& rate : exchangeRates) {
    mkt1.addBondPrice(rate.currencyPair,rate.rate);
    
  }
   for (const BONDSTOCK& rate : stock) {
    mkt1.addStockPrice(rate.currencyPair,rate.rate);
    
  }
  VolCurve volatility = VolCurve();
  RateCurve rates = RateCurve(); 
  std::vector<Volt> rated;
  std::vector<Volt> Vol;
  std::vector<std::string> voltimeSteps;
  std::vector<std::string> ratetimeSteps;
  readFromFilecurves("curve.txt", rated);
  readFromFilecurves("vol.txt",Vol);
  for (const Volt& rate :rated) 
  {
    Date ratetenor = valueDate.addTimeStep(rate.timeStep);
    rates.addRate(ratetenor,rate.value);
  }
  for (const Volt& vol :Vol) 
  {
    Date voltenor = valueDate.addTimeStep(vol.timeStep);
    volatility.addVol(voltenor,vol.value);
  }
  mkt1.addCurve("USD-SOFR",rates);
 mkt1.addVolCurve("Volatility",volatility);
  mkt1.Print();


 // std::vector<std::string> voltimeSteps = {"1M", "3M", "6M", "9M", "1Y", "2Y", "5Y", "10Y"};
  //std::vector<std::string> ratetimeSteps = {"0M", "3M", "6M", "9M", "1Y", "2Y", "5Y", "10Y"};
  //std::vector<double> volRates = {25.6,20.1,18.7,15.4,14.3,14.9,14.5,13.5};
 // std::vector<double> Rates = {5.56,5.5,5.45,5.4,5.53,5.34,4.75,3.90};
 // for (int i = 0; i < voltimeSteps.size(); i++) {
    // Parse time step into a date (assuming a way to convert from string to Date)
   // Date voltenor = valueDate.addTimeStep(voltimeSteps.at(i));
   // Date ratetenor = valueDate.addTimeStep(ratetimeSteps.at(i)); // Implement parseTimeStepToDate function
   // volatility.addVol(voltenor, volRates.at(i));
   // rate.addRate(ratetenor,Rates.at(i));
 // };
 // mkt1.addCurve("USD-SOFR",rate);
 // mkt1.addVolCurve("Volatility",volatility);
 // mkt1.Print();

  /*
  load data from file and update market object with data
  */

  //task 2, create a portfolio of bond, swap, european option, american option
  //for each time, at least should have long / short, different tenor or expiry, different underlying
  //totally no less than 16 trades
  OptionType americano;
  OptionType europeano;
  vector<Trade*> myPortfolio;
  Trade* bond = new Bond(Date(2024, 1, 3), Date(2034, 1, 1), 1000, 103.5);
  myPortfolio.emplace_back(bond);
  Trade* bond2 = new Bond(Date(2024, 2, 1), Date(2034, 1, 1), 200, 105.5);
  myPortfolio.emplace_back(bond2);
  Trade* bond3 = new Bond(Date(2024, 5, 1), Date(2034, 1, 1), 1300, 123.5);
  myPortfolio.emplace_back(bond3);
  Trade* bond4 = new Bond(Date(2024, 3, 1), Date(2034, 1, 1), 1700, 143.5);
  myPortfolio.emplace_back(bond4);
  Trade* american = new AmericanOption(americano=Call,1000,Date(2025, 1, 17));
  myPortfolio.emplace_back(american);
  Trade* american2 = new AmericanOption(americano=Put,11000,Date(2025, 2, 17));
  myPortfolio.emplace_back(american2);
  Trade* american3 = new AmericanOption(americano=BinaryCall,12000,Date(2025, 8, 20));
  myPortfolio.emplace_back(american3);
  Trade* american4 = new AmericanOption(americano=BinaryPut,13000,Date(2025, 1, 19));
  myPortfolio.emplace_back(american4);
  Trade* european = new EuropeanOption(europeano=Call,400,Date(2025, 1, 23));
  myPortfolio.emplace_back(european);
  Trade* european2= new EuropeanOption(europeano=Put,100,Date(2025, 1, 24));
  myPortfolio.emplace_back(european2);
  Trade* european3 = new EuropeanOption(europeano=BinaryCall,100,Date(2025, 1, 25));
  myPortfolio.emplace_back(european3);
  Trade* european4 = new EuropeanOption(europeano=BinaryPut,100,Date(2025, 1, 26));
  myPortfolio.emplace_back(european4);
  Trade* swap= new Swap(Date(2024, 1, 1), Date(2094, 1, 1),1040,1220,1,0.05);
  myPortfolio.emplace_back(swap);
  Trade* swap2= new Swap(Date(2024, 8, 1), Date(2094, 1, 1),1023,1320,2,0.06);
  myPortfolio.emplace_back(swap2);
  Trade* swap3= new Swap(Date(2024, 6, 1), Date(2094, 1, 1),1000,1420,1,0.07);
  myPortfolio.emplace_back(swap3);
  Trade* swap4= new Swap(Date(2024, 5, 1), Date(2094, 1, 1),1908,1550,2,0.09);
  myPortfolio.emplace_back(swap4);
  //task 3, creat a pricer and price the portfolio, output the pricing result of each deal.
  cout << "\nTask 3 - Pricing Portfolio" << endl;
  Pricer* treePricer = new CRRBinomialTreePricer(10);
  for (auto trade: myPortfolio) {
    double pv = treePricer->Price(mkt1, trade);
    cout << fixed << setprecision(2) << pv << endl;
    }
    ofstream resultFile("Task 3.txt");
    resultFile << "Task 3 - Portfolio Net Present Value" << "\n" << "\n";
    double totalPV = 0.0;
    int tradeID = 1;

    for (auto trade: myPortfolio){
        double pv = treePricer->Price(mkt1, trade);
        totalPV += pv;
        if (trade->getType() == "BondTrade"){
            Bond* bondptr = dynamic_cast<Bond*>(trade);
            resultFile << "Trade ID: "<< tradeID << ". " << trade->getType() << ", "
            << "Start Date of Bond: " <<bondptr->getstartdate() << ", " 
            << "Maturity Date of Bond: " << bondptr->getenddate() << ", "
            << "Notional value: " << bondptr->getnotional() << ", " 
            << "Traded Price: " << bondptr->getTradeprice() * bondptr->getnotional() << ", "
            << "Current PV: " << pv << "\n" << "\n";
            tradeID += 1;
        }
         else if (trade->getType() == "SwapTrade"){
            Swap* swapptr = dynamic_cast<Swap*>(trade);
            resultFile << "Trade ID: " << tradeID << ". " << trade->getType() << ", "
            << "Start Date of Contract: " << swapptr->getstart() << ", "
            << "Maturity Date of Contract: " << swapptr->getend() << ", "
            << "Notional: " << swapptr->getnotional() << ", "
            << "Traded Rate: " << swapptr->gettraderate() << ", "
            << "Payment Frequency per year: " << swapptr->gettfrequency() << ", "
            << "Current PV: " << pv << "\n" << "\n";
            tradeID += 1;
        }
        else if (trade->getType() == "TreeProduct"){
            EuropeanOption* eur = dynamic_cast<EuropeanOption*>(trade);
            if (eur){ // mean this is European option
            resultFile << "Trade ID: " << tradeID << ". " << trade->getType() << "European Option" << ", "
            << "Option type: " << eur->getoptType() << ", "
            << "Expiry Date: " << eur->getdate() << ", "
            << "Strike price: " << eur->getstrike() << ", "
            << "Present Value: " << pv << "\n" << "\n";
            tradeID += 1;
            }
            else{
            AmericanOption* amr = dynamic_cast<AmericanOption*>(trade);
            resultFile << "Trade ID: " << tradeID << ". " << trade->getType() << "European Option" << ", "
            << "Option type: " << amr->getoptType() << ", "
            << "Expiry Date: " << amr->getdate() << ", "
            << "Strike price: " << amr->getstrike() << ", "
            << "Present Value: " << pv << "\n" << "\n";
            tradeID += 1;
        }
    }
    }
    //log pv details out in a file
  resultFile << "Total PV of the portfolio is: " << totalPV << endl;

  //task 4, analyzing pricing result
  // a) compare CRR binomial tree result for an european option vs Black model
  // b) compare CRR binomial tree result for an american option vs european option
  EuropeanOption euro =  EuropeanOption(europeano = Call,10000,Date(2026,2,1));
  AmericanOption amerio = AmericanOption (americano = Call,70000,Date(2028,2,2));
  double strike =80000;
  double spot_price = 80000;
  double vvol = 0.35;
  double riskfreerate = 0.35;
  double americant  = (amerio.GetExpiry()-valueDate );  
  double eurot  = (euro.GetExpiry()-valueDate) ;
  CRRBinomialTreePricer treePricers(100);
  double epriceTree = treePricers.PriceTree(mkt1, euro);
  double  priceTree = treePricers.PriceTree(mkt1, amerio);
  double  blackmodel = BlackScholesPrice(spot_price, strike, eurot, riskfreerate, vvol, Call);
  cout << "Price of the European option with CRR Binomial Tree: " << epriceTree << endl;
  cout << "Price of the European option with Black-Scholes: " << blackmodel << endl;
  ofstream resultFile2("Task 4.txt");
   resultFile2 << "A: CRR Binomial Tree and Black-Scholes" << "\n" << "\n"
    << "Price of the European option with CRR Binomial Tree: " << epriceTree << "\n"
    << "Price of the European option with Black-Scholes: " << blackmodel << "\n" << "\n";
   resultFile2 << "B: CRR Binomial for European VS American Option" << "\n" << "\n"
    << "Price of the European option with CRR Binomial Tree: " << epriceTree << "\n"
    << "Price of the American option with CRR Binomial Tree: " << priceTree;

  //final
  cout << "Project build successfully!" << endl;
  return 0;
}

