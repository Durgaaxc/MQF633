#include <fstream>
#include <ctime>
#include <chrono>

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
int x[8] = {19, 10, 8, 17, 9, 15};

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
  rate.addRate(valueDate,5.56);
  valueDate.month += 1;
  volatility.addVol(valueDate,25.6);
  valueDate.month += 2;
  volatility.addVol(valueDate,20.1);
  valueDate.month += 3;
  volatility.addVol(valueDate,18.7);
  rate.addRate(valueDate,5.5);
  valueDate.month += 1;
  volatility.addVol(valueDate,15.4);
  rate.addRate(valueDate,5.45);
  valueDate.month += 3;
  rate.addRate(valueDate,5.4);


  valueDate.month =now_->tm_mon + 1;
  valueDate.year +=1;
  volatility.addVol(valueDate,14.3);
  rate.addRate(valueDate,5.53);
  valueDate.year +=1;
  volatility.addVol(valueDate,14.9);
  rate.addRate(valueDate,5.34);
  valueDate.year +=3;
  volatility.addVol(valueDate,14.5);
  rate.addRate(valueDate,4.75);
  valueDate.year +=5;
  volatility.addVol(valueDate,13.5);
  rate.addRate(valueDate,3.90);
  mkt1.addCurve("USD-SOFR",rate);
  mkt1.addVolCurve("Volatility",volatility);
  mkt1.Print();
  /*
  load data from file and update market object with data
  */

  //task 2, create a portfolio of bond, swap, european option, american option
  //for each time, at least should have long / short, different tenor or expiry, different underlying
  //totally no less than 16 trades
  vector<Trade*> myPortfolio;
  Trade* bond = new Bond(Date(2024, 1, 1), Date(2034, 1, 1), 1000, 103.5);
  myPortfolio.push_back(bond);
  Trade* bond2 = new Bond(Date(2024, 1, 1), Date(2034, 1, 1), 200, 105.5);
  myPortfolio.push_back(bond2);
  Trade* bond3 = new Bond(Date(2024, 1, 1), Date(2034, 1, 1), 1300, 123.5);
  myPortfolio.push_back(bond3);
  Trade* bond4 = new Bond(Date(2024, 1, 1), Date(2034, 1, 1), 1700, 143.5);
  myPortfolio.push_back(bond4);
  OptionType americano;
  OptionType europeano;
  Trade* american = new AmericanOption(americano=Call,100,Date(2025, 1, 17));
  myPortfolio.push_back(american);
  Trade* american2 = new AmericanOption(americano=Put,110,Date(2025, 2, 17));
  myPortfolio.push_back(american2);
  Trade* american3 = new AmericanOption(americano=BinaryCall,120,Date(2025, 8, 20));
  myPortfolio.push_back(american3);
  Trade* american4 = new AmericanOption(americano=BinaryPut,130,Date(2025, 1, 19));
  myPortfolio.push_back(american4);
  Trade* european = new EuropeanOption(europeano=Call,400,Date(2025, 1, 23));
  myPortfolio.push_back(european);
  Trade* european2= new EuropeanOption(europeano=Put,100,Date(2025, 1, 24));
  myPortfolio.push_back(european2);
  Trade* european3 = new EuropeanOption(europeano=BinaryCall,100,Date(2025, 1, 25));
  myPortfolio.push_back(european3);
  Trade* european4 = new EuropeanOption(europeano=BinaryPut,100,Date(2025, 1, 26));
  myPortfolio.push_back(european4);
  
  Trade* swap= new Swap(Date(2024, 1, 1), Date(2094, 1, 1),10400,1220,1,0.05);
  myPortfolio.push_back(swap);
  Trade* swap2= new Swap(Date(2024, 1, 1), Date(2094, 1, 1),10230,1320,2,0.06);
  myPortfolio.push_back(swap2);
  Trade* swap3= new Swap(Date(2024, 1, 1), Date(2094, 1, 1),1000,1420,1,0.07);
  myPortfolio.push_back(swap3);
  Trade* swap4= new Swap(Date(2024, 1, 1), Date(2094, 1, 1),1908,1550,2,0.09);
   myPortfolio.push_back(swap4);
  //task 3, creat a pricer and price the portfolio, output the pricing result of each deal.
  Pricer* treePricer = new CRRBinomialTreePricer(10);
  std::ofstream outputFile("pricing_results.txt");
  for (auto trade: myPortfolio) {
    double pv = treePricer->Price(mkt1, trade);
    outputFile << "Trade Type: " << trade ->getType() << std::endl;
    outputFile << "Price: " << pv << std::endl;
    outputFile << "----------------------" << std::endl;};
    
   
    //log pv details out in a file

  //}

  //task 4, analyzing pricing result
  // a) compare CRR binomial tree result for an european option vs Black model
  // b) compare CRR binomial tree result for an american option vs european option

  //final
  //cout << "Project build successfully!" << endl;
  //return 0;

}
