#ifndef _PRICER
#define _PRICER

#include <vector>
#include <cmath>

#include "Trade.h"
#include "TreeProduct.h"
#include "Market.h"

// Interface for the Pricer class
class Pricer {
public:
    virtual double Price(const Market& mkt, Trade* trade);

private:
    // Make PriceTree a pure virtual function
    virtual double PriceTree(const Market& mkt, const TreeProduct& trade) = 0;
};

// Implementation of the BinomialTreePricer class
class BinomialTreePricer: public Pricer {
public:
    // Constructor taking number of time steps
    BinomialTreePricer(int N) : nTimeSteps(N) {
        states.resize(N+1);
    }

    // Override PriceTree method
    double PriceTree(const Market& mkt, const TreeProduct& trade) override;
  
protected:
    // Pure virtual functions for model setup
    virtual void ModelSetup(double S0, double sigma, double rate, double dt) = 0;
    virtual double GetSpot(int ti, int si) const = 0;
    virtual double GetProbUp() const = 0;
    virtual double GetProbDown() const = 0;
  
private:
    int nTimeSteps;
    std::vector<double> states;
};

// Implementation of the CRRBinomialTreePricer class
class CRRBinomialTreePricer : public BinomialTreePricer {
public:
    // Constructor taking number of time steps
    CRRBinomialTreePricer(int N) : BinomialTreePricer(N) {}

protected:
    void ModelSetup(double S0, double sigma, double rate, double dt) override; 
    double GetSpot(int ti, int si) const override {
        return currentSpot * std::pow(u, ti-2*si); 
    }
    double GetProbUp() const override { return p; }
    double GetProbDown() const override { return 1-p; }
  
private:
    double u; // up multiplicative
    double p; // probability for up state
    double currentSpot; // current market spot price
};

// Implementation of the JRRNBinomialTreePricer class
class JRRNBinomialTreePricer : public BinomialTreePricer {
public:
    // Constructor taking number of time steps
    JRRNBinomialTreePricer(int N) : BinomialTreePricer(N) {}
 
protected:
    void ModelSetup(double S0, double sigma, double rate, double dt) override;
  
    double GetSpot(int ti, int si) const override {
        return currentSpot * std::pow(u, ti-si) * std::pow(d, si);
    }
    double GetProbUp() const override { return p; }
    double GetProbDown() const override { return 1-p; }

private:
    double u; // up multiplicative
    double d; // down multiplicative
    double p; // probability for up state
    double currentSpot; // current market spot price
}; 

#endif
