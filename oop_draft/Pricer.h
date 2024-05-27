// Pricer.h
#ifndef _PRICER_H
#define _PRICER_H

#include "Market.h"
#include "Trade.h" // Include Trade header
#include "TreeProduct.h" // Include TreeProduct header

// Forward declaration of Trade and TreeProduct
class Trade;
class TreeProduct;

// Interface
class Pricer {
public:
    virtual double Price(const Market& mkt, Trade* trade);

    // Declare other virtual functions or members as needed
};

class CRRBinomialTreePricer : public Pricer {
public:
    CRRBinomialTreePricer(int steps) : steps(steps) {}
    
    double PriceEuropeanOption(double S, double K, double T, double r, double sigma);
    double PriceAmericanOption(double S, double K, double T, double r, double sigma);

private:
    int steps;
};

#endif // _PRICER_H
