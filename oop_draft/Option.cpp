#include "Option.h"
#include "Market.h"
#include <cmath>

double BlackScholesPrice(const Option* option, const Market* market) {
    double S = market->getStockPrice("default_stock"); // Placeholder, replace with actual logic
    double r = market->getInterestRate(option->getExpiry());
    double sigma = market->getVolatility(option->getExpiry());
    double T = (option->getExpiry() - market->asOf) / 365.0;

    double d1 = (std::log(S) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    // Assuming call option, replace with actual pricing formula as needed
    double callPrice = S * std::exp(-r * T) * d1 - std::exp(-r * T) * d2;
    return callPrice;
}
