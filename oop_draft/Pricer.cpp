#include <cmath>
#include <vector>
#include "Pricer.h"
#include "TreeProduct.h"
#include "Market.h"
#include "Trade.h"

// Define BinomialTreePricerBase class
class BinomialTreePricerBase {
protected:
    int nTimeSteps;
    std::vector<double> states; // Use std::vector for states
    virtual double GetProbUp() const = 0;
    virtual double GetProbDown() const = 0;
    virtual double GetSpot(int n, int i) const = 0;
public:
    double PriceTree(const Market& mkt, const TreeProduct& trade);
    virtual void ModelSetup(double S0, double sigma, double rate, double dt) = 0;
};

double BinomialTreePricerBase::PriceTree(const Market& mkt, const TreeProduct& trade) {
    // Model setup
    double T = trade.GetExpiry() - mkt.asOf;
    double dt = T / nTimeSteps;
    double stockPrice, vol, rate;
    // Get these data for the deal from market object
    ModelSetup(stockPrice, vol, rate, dt);

    // Initialize states vector
    states.resize(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; i++) {
        states[i] = trade.Payoff(GetSpot(nTimeSteps, i));
    }

    // Price by backward induction
    for (int k = nTimeSteps - 1; k >= 0; k--) {
        for (int i = 0; i <= k; i++) {
            // Calculate continuation value
            double df = exp(-rate * dt);
            double continuation = df * (states[i] * GetProbUp() + states[i + 1] * GetProbDown());
            // Calculate the option value at node(k, i)
            states[i] = trade.ValueAtNode(GetSpot(k, i), dt * k, continuation);
        }
    }

    return states[0];
}


// Declare CRRBinomialTreePricer class
class CRRBinomialTreePricer : public BinomialTreePricerBase {
private:
    double u, p, currentSpot;
public:
    CRRBinomialTreePricer(int steps) : nTimeSteps(steps) {} // Initialize nTimeSteps in the constructor
    double PriceEuropeanOption(double S, double K, double T, double r, double sigma);
    double PriceAmericanOption(double S, double K, double T, double r, double sigma);
    void ModelSetup(double S0, double sigma, double rate, double dt) override;
    double GetProbUp() const override;
    double GetProbDown() const override;
    double GetSpot(int n, int i) const override;

    // Accessor methods for u and p
    double GetU() const { return u; }
    double GetP() const { return p; }
};

// Define CRRBinomialTreePricer member functions
void CRRBinomialTreePricer::ModelSetup(double S0, double sigma, double rate, double dt) {
    double b = std::exp((2 * rate + sigma * sigma) * dt) + 1;
    u = (b + std::sqrt(b * b - 4 * std::exp(2 * rate * dt))) / 2 / std::exp(rate * dt);
    p = (std::exp(rate * dt) - 1 / u) / (u - 1 / u);
    currentSpot = S0;
}


double CRRBinomialTreePricer::GetProbUp() const {
    return p;
}


double CRRBinomialTreePricer::GetProbDown() const {
    return 1 - p;
}

double CRRBinomialTreePricer::GetSpot(int n, int i) const {
    return currentSpot * pow(u, i) * pow(1 / u, n - i);
}

// Implementation for BinomialEuropeanOption
double CRRBinomialTreePricer::PriceEuropeanOption(double S, double K, double T, double r, double sigma) {
    double dt = T / nTimeSteps;
    double u = exp(sigma * sqrt(dt));
    double d = 1 / u;
    double p = (exp(r * dt) - d) / (u - d);
    std::vector<double> states(nTimeSteps + 1); // Initialize states vector

    // Compute terminal stock prices
    std::vector<double> stockPrices(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        stockPrices[i] = S * pow(u, nTimeSteps - i) * pow(d, i);
    }

    // Compute option payoffs at maturity
    std::vector<double> optionPayoffs(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        optionPayoffs[i] = std::max(0.0, stockPrices[i] - K);
    }

    // Backward induction to compute option price
    for (int j = nTimeSteps - 1; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            optionPayoffs[i] = std::exp(-r * dt) * (p * optionPayoffs[i] + (1 - p) * optionPayoffs[i + 1]);
        }
    }

    return optionPayoffs[0];
}

// Implementation for BinomialAmericanOption
double CRRBinomialTreePricer::PriceAmericanOption(double S, double K, double T, double r, double sigma) {
    double dt = T / nTimeSteps;
    double u = exp(sigma * sqrt(dt));
    double d = 1 / u;
    double p = (exp(r * dt) - d) / (u - d);
    std::vector<double> states(nTimeSteps + 1); // Initialize states vector

    // Compute terminal stock prices
    std::vector<double> stockPrices(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        stockPrices[i] = S * pow(u, nTimeSteps - i) * pow(d, i);
    }

    // Compute option payoffs at maturity
    std::vector<double> optionPayoffs(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        optionPayoffs[i] = std::max(0.0, stockPrices[i] - K);
    }

    // Backward induction to compute option price
    for (int j = nTimeSteps - 1; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            optionPayoffs[i] = std::max(std::exp(-r * dt) * (p * optionPayoffs[i] + (1 - p) * optionPayoffs[i + 1]), stockPrices[i] - K);
        }
    }

    return optionPayoffs[0];
}
// Implementation for BinomialEuropeanOption
double BinomialTreePricer::PriceEuropeanOption(double S, double K, double T, double r, double sigma, int nTimeSteps) {
    double dt = T / nTimeSteps;
    double u = exp(sigma * sqrt(dt));
    double d = 1 / u;
    double p = (exp(r * dt) - d) / (u - d);
    std::vector<double> states(nTimeSteps + 1); // Initialize states vector

    // Compute terminal stock prices
    std::vector<double> stockPrices(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        stockPrices[i] = S * pow(u, nTimeSteps - i) * pow(d, i);
    }

    // Compute option payoffs at maturity
    std::vector<double> optionPayoffs(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        optionPayoffs[i] = std::max(0.0, stockPrices[i] - K);
    }

    // Backward induction to compute option price
    for (int j = nTimeSteps - 1; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            optionPayoffs[i] = std::exp(-r * dt) * (p * optionPayoffs[i] + (1 - p) * optionPayoffs[i + 1]);
        }
    }

    return optionPayoffs[0];
}

// Implementation for BinomialAmericanOption
double BinomialTreePricer::PriceAmericanOption(double S, double K, double T, double r, double sigma, int nTimeSteps) {
    double dt = T / nTimeSteps;
    double u = exp(sigma * sqrt(dt));
    double d = 1 / u;
    double p = (exp(r * dt) - d) / (u - d);
    std::vector<double> states(nTimeSteps + 1); // Initialize states vector

    // Compute terminal stock prices
    std::vector<double> stockPrices(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        stockPrices[i] = S * pow(u, nTimeSteps - i) * pow(d, i);
    }

    // Compute option payoffs at maturity
    std::vector<double> optionPayoffs(nTimeSteps + 1);
    for (int i = 0; i <= nTimeSteps; ++i) {
        optionPayoffs[i] = std::max(0.0, stockPrices[i] - K);
    }

    // Backward induction to compute option price
    for (int j = nTimeSteps - 1; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            optionPayoffs[i] = std::max(std::exp(-r * dt) * (p * optionPayoffs[i] + (1 - p) * optionPayoffs[i + 1]), stockPrices[i] - K);
        }
    }

    return optionPayoffs[0];
}
