#ifndef SWAP_H
#define SWAP_H

#include "Trade.h"
#include "Market.h"
#include "Date.h"

class Swap : public Trade {
public:
    Swap(Date start, Date end, double _notional, double _price, double _frequency)
        : Trade("SwapTrade", start), startDate(start), maturityDate(end),
          notional(_notional), tradeRate(_price), frequency(_frequency) {}

    double Payoff(double marketPrice, const Market& mkt) const;

    double getAnnuity(const Market& mkt) const;

private:
    Date startDate;
    Date maturityDate;
    double notional;
    double tradeRate;
    double frequency;
};

#endif
