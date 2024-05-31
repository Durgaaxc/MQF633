#ifndef MARKET_H
#define MARKET_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Date.h"

using namespace std;

class RateCurve {
public:
    RateCurve() {}
    RateCurve(const string& _name): name(_name) {}
    void addRate(Date tenor, double rate);
    double getRate(Date tenor) const;
    void display() const;

private:
    string name;
    vector<Date> tenors;
    vector<double> rates;
};

class VolCurve {
public:
    VolCurve() {}
    VolCurve(const string& _name): name(_name) {}
    void addVol(Date tenor, double vol);
    double getVol(Date tenor) const;
    void display() const;

private:
    string name;
    vector<Date> tenors;
    vector<double> vols;
};

class Market {
public:
    Date asOf;
    Market(const Date& now): asOf(now) {}
    void Print() const;
    void addCurve(const std::string& curveName, const RateCurve& curve);
    void addVolCurve(const std::string& curveName, const VolCurve& curve);
    void addBondPrice(const std::string& bondName, double price);
    void addStockPrice(const std::string& stockName, double price);

    void updateInterestRateCurves(const std::string& curveData);
    void updateVolatilityCurves(const std::string& volData);
    void updateBondPrices(const std::string& bondPriceData);
    void updateStockPrices(const std::string& stockPriceData);

    double getStockPrice(const std::string& stockName) const;
    double getInterestRate(const Date& expiry) const;
    double getVolatility(const Date& expiry) const;

    inline RateCurve getCurve(const string& name) { return curves[name]; }
    inline VolCurve getVolCurve(const string& name) { return vols[name]; }

private:
    unordered_map<string, VolCurve> vols;
    unordered_map<string, RateCurve> curves;
    unordered_map<string, double> bondPrices;
    unordered_map<string, double> stockPrices;
};

std::ostream& operator<<(std::ostream& os, const Market& obj);
std::istream& operator>>(std::istream& is, Market& obj);

#endif // MARKET_H
