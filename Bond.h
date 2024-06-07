#pragma once
#include "Trade.h"

class Bond : public Trade {
public:
    Bond(Date start, Date end, double _notional, double _price): Trade("BondTrade", start) {
        notional = _notional;
        tradePrice = _price;
        startDate = start;
        maturityDate = end;
    }

    inline double Payoff(double marketPrice) const { 
        return notional-tradePrice;
        }; // implement this
     inline Date getstartdate() const { 
        return startDate ;
        }; 
        inline Date getenddate() const { 
        return maturityDate ;
        }; 
         inline double getnotional() const { 
        return notional;
        };
         inline double getTradeprice() const { 
        return tradePrice;
        };
private:
    double notional;
    double tradePrice;
    Date startDate;
    Date maturityDate;
};