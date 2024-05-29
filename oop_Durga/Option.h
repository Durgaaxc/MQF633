#ifndef OPTION_H
#define OPTION_H

#include "Date.h"
#include "Market.h"

class Option {
public:
    Option(const Date& expiry): expiry(expiry) {}
    virtual ~Option() = default;
    Date getExpiry() const { return expiry; }

private:
    Date expiry;
};

class EuropeanOptionBase : public Option {
public:
    EuropeanOptionBase(const Date& expiry): Option(expiry) {}
};

double BlackScholesPrice(const Option* option, const Market* market);

#endif // OPTION_H
