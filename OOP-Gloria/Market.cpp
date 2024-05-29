#include "Market.h"
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

void RateCurve::display() const {
    cout << "rate curve:" << name << endl;
    for (size_t i=0; i<tenors.size(); i++) {
      cout << tenors[i] << ":" << rates[i] << endl;
  }
  cout << endl;
}

void RateCurve::addRate(Date tenor, double rate) {
  //consider to check if tenor already exist
  if (true){
    tenors.push_back(tenor);
    rates.push_back(rate);
  }  
}

double RateCurve::getRate(Date tenor) const {
  double dx = tenors.at(1)-tenors.at(0);
  double dy = rates.at(1)-rates.at(0);
  double gradient  = dy/dx;
  // it = std::find(tenors.begin(), tenors.end(), tenor);
  //if (it != tenors.end()) {
        //int index = std::distance(tenors.begin(), it);
    //} 
  double dx1 = tenor - tenors.at(0);
  double Rate = rates.at(0) + gradient * dx1;
  return Rate;
}
double VolCurve::getVol(Date tenor) const {
  double dx = tenors.at(1)-tenors.at(0);
  double dy = vols.at(1)-vols.at(0);
  double gradient  = dy/dx;
  // it = std::find(tenors.begin(), tenors.end(), tenor);
  //if (it != tenors.end()) {
        //int index = std::distance(tenors.begin(), it);
    //} 
  double dx1 = tenor - tenors.at(0);
  double VOLAtility = vols.at(0) + gradient * dx1;
  return VOLAtility;
}


void VolCurve::display() const {
      cout << "volatitlity curve:" << name << endl;
    for (size_t i=0; i<tenors.size(); i++) {
      cout << tenors[i] << ":" << vols[i] << endl;
  }
  cout << endl;
}

void Market::addStockPrice(const std::string& stockName, double price) {
  stockPrices.emplace(stockName, price);
}
void Market::addVolCurve(const std::string& curveName, const VolCurve& curve)
{
  vols.emplace(curveName,curve);
}
void VolCurve::addVol(Date tenor, double rate)
{
  tenors.push_back(tenor);
  vols.push_back(rate);
}


void Market::Print() const
{
  cout << "market asof: " << asOf << endl;
  
  for (auto curve: curves) {
    curve.second.display();
  }
  for (auto vol: vols) {
    vol.second.display();
  }
  for (const auto& pair : bondPrices) {
        std::cout << "Bond: " << pair.first << ", Price: " << pair.second << std::endl;
    }

    // Displaying stock prices
    for (const auto& pair : stockPrices) {
        std::cout << "Stock: " << pair.first << ", Price: " << pair.second << std::endl;
    }

}

void Market::addCurve(const std::string& curveName, const RateCurve& curve){
  curves.emplace(curveName, curve);
}
void Market::addBondPrice(const std::string& bondName, double price) {
  bondPrices.emplace(bondName,price);
}


std::ostream& operator<<(std::ostream& os, const Market& mkt)
{
  os << mkt.asOf << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Market& mkt)
{
  is >> mkt.asOf;
  return is;
}
