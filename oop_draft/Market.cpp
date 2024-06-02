#include "Market.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

namespace
{
    // for string delimiter
    std::vector<std::string> split(std::string s, std::string delimiter) 
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    };
    
    Date getTenorFromStr(const string& tenorStr, const Date& today)
    {
        if(tenorStr == "ON"){
            return DateAddDay(today, 1);
        }
        else if(tenorStr =="1W"){
            return DateAddDay(today, 7);
        }
        else if(tenorStr =="1M"){
            return DateAddDay(today, 30);
        }
        else if(tenorStr =="1Y"){
            return DateAddDay(today, 365);
        }
        else{
            return today;
        }
        return today;
    }

} 
// namespace


void RateCurve::display() const {
    cout << "Rate curve: " << name << endl;
    for (size_t i = 0; i < tenors.size(); i++) {
        cout << tenors[i] << ": " << rates[i] << endl;
    }
    cout << endl;
}

void RateCurve::addRate(Date tenor, double rate) {
    auto it = std::lower_bound(tenors.begin(), tenors.end(), tenor);
    if (it != tenors.end() && *it == tenor) { // this line is wrong, there is no "==" behaviour for Date class object
        cerr << "Tenor already exists." << endl;
        return;
    }
    tenors.push_back(tenor); // use tenor.push_back(tenor);
    rates.push_back(rate); //use rates.push_back(rate);
}

double RateCurve::getRate(Date tenor) const {
    // if (tenors.empty() || tenor < tenors.front() || tenor > tenors.back()) {
    //     cerr << "Invalid tenor." << endl;
    //     return 0;
    // }
    //dont need this, if tenor is smaller than 1st one return first value, if tenor is later than last one return last value

    auto it = std::upper_bound(tenors.begin(), tenors.end(), tenor);
    if (it == tenors.begin()) {
        cerr << "Invalid tenor." << endl;
        return 0;
    }
    size_t idx = it - tenors.begin();
    Date t1 = tenors[idx - 1];
    Date t2 = *it;
    double r1 = rates[idx - 1];
    double r2 = rates[idx];
    double rate = r1 + ((r2 - r1) / (t2 - t1)) * (tenor - t1);
    return rate;
}

void VolCurve::display() const {
    cout << "Volatility curve: " << name << endl;
    for (size_t i = 0; i < tenors.size(); i++) {
        cout << tenors[i] << ": " << vols[i] << endl;
    }
    cout << endl;
}

void VolCurve::addVol(Date tenor, double vol) {
    auto it = std::lower_bound(tenors.begin(), tenors.end(), tenor);
    if (it != tenors.end() && *it == tenor) {
        cerr << "Tenor already exists." << endl;
        return;
    }
    tenors.insert(it, tenor);
    vols.insert(vols.begin() + (it - tenors.begin()), vol);
}

double VolCurve::getVol(Date tenor) const {
    if (tenors.empty() || tenor < tenors.front() || tenor > tenors.back()) {
        cerr << "Invalid tenor." << endl;
        return 0;
    }
    auto it = std::upper_bound(tenors.begin(), tenors.end(), tenor);
    if (it == tenors.begin()) {
        cerr << "Invalid tenor." << endl;
        return 0;
    }
    size_t idx = it - tenors.begin();
    Date t1 = tenors[idx - 1];
    Date t2 = *it;
    double v1 = vols[idx - 1];
    double v2 = vols[idx];
    double vol = v1 + ((v2 - v1) / (t2 - t1)) * (tenor - t1);
    return vol;
}

void Market::Print() const {
    cout << "Market as of: " << asOf << endl;
    cout << "Interest Rate Curves:" << endl;
    for (const auto& curve : curves) {
        curve.second.display();
    }
    cout << "Volatility Curves:" << endl;
    for (const auto& vol : vols) {
        vol.second.display();
    }
    cout << "Bond Prices:" << endl;
    for (const auto& bondPrice : bondPrices) {
        cout << bondPrice.first << ": " << bondPrice.second << endl;
    }
    cout << "Stock Prices:" << endl;
    for (const auto& stockPrice : stockPrices) {
        cout << stockPrice.first << ": " << stockPrice.second << endl;
    }
}

void Market::addCurve(const std::string& curveName, const RateCurve& curve) {
    curves.emplace(curveName, curve);
}

void Market::addVolCurve(const std::string& curveName, const VolCurve& curve) {
    vols.emplace(curveName, curve);
}

void Market::addBondPrice(const std::string& bondName, double price) {
    bondPrices.emplace(bondName, price);
}

void Market::addStockPrice(const std::string& stockName, double price) {
    stockPrices.emplace(stockName, price);
}

void Market::updateInterestRateCurves(const std::string& curveData) {
    // istringstream iss(curveData);
    // string line;
    // while (getline(iss, line)) {
    //     istringstream lineStream(line);
    //     string curveName;
    //     Date tenor;
    //     double rate;
    //     lineStream >> curveName >> tenor >> rate;
    //     if (curves.find(curveName) == curves.end()) {
    //         curves[curveName] = RateCurve(curveName);
    //     }
    //     curves[curveName].addRate(tenor, rate);
    // }
    vector<string> data = split(curveData, ";");
    string name = data[0];
    RateCurve curve(name);
    for (size_t i = 1; i<data.size(); i++) {
        string pair = data[i];
        vector<string> pair_split = split(pair, ": ");
        if (pair_split.size() ==1)
            continue;
        string tenor_ = pair_split[0];
        string value_ = pair_split[1];
        double rate_ = std::stod(value_);
        auto tenor = getTenorFromStr(tenor_, this->asOf);
        curve.addRate(tenor, rate_/100);
    }


}

void Market::updateVolatilityCurves(const std::string& volData) {
    istringstream iss(volData);
    string line;
    while (getline(iss, line)) {
        istringstream lineStream(line);
        string volCurveName;
        Date tenor;
        double vol;
        lineStream >> volCurveName >> tenor >> vol;
        if (vols.find(volCurveName) == vols.end()) {
            vols[volCurveName] = VolCurve(volCurveName);
        }
        vols[volCurveName].addVol(tenor, vol);
    }
}

void Market::updateBondPrices(const std::string& bondPriceData) {
    istringstream iss(bondPriceData);
    string line;
    while (getline(iss, line)) {
        istringstream lineStream(line);
        string bondName;
        double price;
        lineStream >> bondName >> price;
        bondPrices[bondName] = price;
    }
}

void Market::updateStockPrices(const std::string& stockPriceData) {
    istringstream iss(stockPriceData);
    string line;
    while (getline(iss, line)) {
        istringstream lineStream(line);
        string stockName;
        double price;
        lineStream >> stockName >> price;
        stockPrices[stockName] = price;
    }
}

double Market::getStockPrice(const std::string& stockName) const {
    auto it = stockPrices.find(stockName);
    if (it != stockPrices.end()) {
        return it->second;
    }
    cerr << "Stock not found." << endl;
    return 0.0;
}

double Market::getInterestRate(const Date& expiry) const {
    // Assuming we use a default interest rate curve name, replace with actual logic as needed
    string defaultCurveName = "default_curve";
    auto it = curves.find(defaultCurveName);
    if (it != curves.end()) {
        return it->second.getRate(expiry);
    }
    cerr << "Interest rate curve not found." << endl;
    return 0.0;
}

double Market::getVolatility(const Date& expiry) const {
    // Assuming we use a default volatility curve name, replace with actual logic as needed
    string defaultVolCurveName = "default_vol_curve";
    auto it = vols.find(defaultVolCurveName);
    if (it != vols.end()) {
        return it->second.getVol(expiry);
    }
    cerr << "Volatility curve not found." << endl;
    return 0.0;
}

std::ostream& operator<<(std::ostream& os, const Market& mkt) {
    os << mkt.asOf << endl;
    return os;
}

std::istream& operator>>(std::istream& is, Market& mkt) {
    is >> mkt.asOf;
    return is;
}
