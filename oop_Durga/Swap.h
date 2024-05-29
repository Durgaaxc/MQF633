#pragma once
#include "Trade.h"
#include "Date.h"
#include <cmath>

class Swap : public Trade {
public:
    Swap(Date start, Date end, double _notional, double _price, double _tradeRate, double _frequency) 
        : Trade("SwapTrade", start), startDate(start), maturityDate(end), notional(_notional), 
        tradePrice(_price), tradeRate(_tradeRate), frequency(_frequency) {}

    double Payoff(double marketPrice) const { 
        return getAnnuity() * (tradeRate - marketPrice); 
    }

    double getAnnuity() const {
        double annuity = 0.0;
        double dt = 1.0 / frequency; // Time between payments in years (e.g., 1 for annual, 0.5 for semi-annual)
        
        Date d = startDate;
        while (d < maturityDate) {
            double discountFactor = std::exp(-tradeRate * (d - startDate));
            annuity += notional * discountFactor;
            // Increment the date according to the frequency
            incrementDate(d);
        }
        return annuity;
    }

private:
    Date startDate;
    Date maturityDate;
    double notional;
    double tradePrice;
    double tradeRate;
    double frequency; // Use 1 for annual, 2 for semi-annual, etc.

    void incrementDate(Date& date) const {
        int monthsToAdd = static_cast<int>(12 / frequency);
        date.month += monthsToAdd;
        if (date.month > 12) {
            date.year += date.month / 12;
            date.month = date.month % 12;
        }
    }
};
