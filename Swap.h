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
    double Payoff(double marketrate) const{
    // Calculate the present value (PV) of the swap
    double annuity = getAnnuity();
    return (annuity * (tradeRate - marketrate));
    }; 
    inline Date getstart()
    {
        return startDate;
    }
    inline Date getend()
    {
        return maturityDate;
    }
     inline double getnotional()
    {
        return notional;
    }
    inline double gettraderate()
    {
        return tradeRate;
    }
    inline double gettfrequency()
    {
        return frequency;
    }

    // Function to calculate the annuity
    double getAnnuity() const{
      double annuity = 0.0;
      int periods = (maturityDate.year - startDate.year) * frequency; // Total number of periods
      double periodLength = 1.0 / frequency; // Length of each period in years

      for (int i = 1; i <= periods; ++i) {
          double time = i * periodLength;
          double discountFactor = exp(-tradeRate * time);
          annuity += notional * discountFactor;
      }

        return annuity;
  }

private:
    Date startDate;
    Date maturityDate;
    double notional;
    double tradeRate;
    double frequency; // use 1 for annual, 2 for semi-annual etc
};