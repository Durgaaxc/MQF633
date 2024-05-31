#pragma once
#include "Trade.h"
#include "Date.h"
#include <cmath>


class Swap : public Trade {
public:
    // Constructor
    Swap(Date start, Date end, double _notional, double _price, double _frequency, double _tradeRate)
        : Trade("SwapTrade", start), startDate(start), maturityDate(end), notional(_notional), frequency(_frequency), tradeRate(_tradeRate) {}

    // Function to calculate the payoff
    double Payoff(double marketPrice) const {    
        double annuity = getAnnuity();
    return annuity * (tradeRate - marketPrice);
    };

    // Function to calculate the annuity
    double getAnnuity() const{ double annuity = 0.0;
    double timeStep = 1.0 / frequency;
    for (int period = 1; period <= frequency; ++period) {
        double discountFactor = exp(-tradeRate * period * timeStep);
        annuity += notional * discountFactor;
    }
    return annuity;
    };

private:
    Date startDate;
    Date maturityDate;
    double notional;
    double tradeRate;
    double frequency; // use 1 for annual, 2 for semi-annual etc
};