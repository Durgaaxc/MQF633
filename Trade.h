#pragma once
#include<string>
#include "Date.h"

using namespace std;

class Trade {
public:
    Trade(){};
    Trade(const string& _type,Date _tradeDate): tradeType(_type), tradeDate(_tradeDate) {};
    inline string getType(){ return tradeType; };
    virtual double Payoff(double marketPrice) const = 0;
    inline Date getDate(){ return tradeDate; };
    virtual ~Trade(){};

protected:   
    string tradeType;
    Date tradeDate;
    Date MaturityDate;
};