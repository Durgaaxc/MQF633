#pragma once
#include "Trade.h"

class Bond : public Trade {
public:
    // Constructor with necessary details
    Bond(Date start, Date end, double _notional, double _price): Trade("BondTrade", start),
        startDate(start), maturityDate(end), notional(_notional), tradePrice(_price) {}

    // Implement the Payoff function
    inline double Payoff(double marketPrice) const { return marketPrice - tradePrice; }

private:
    double notional;
    double tradePrice;
    Date startDate;
    Date maturityDate;
};
