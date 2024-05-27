#include "Market.h"
#include "Date.h"
#include <iostream>

// Implementation of RateCurve member functions
void RateCurve::display() const {
    std::cout << "rate curve: " << name << std::endl;
    for (size_t i = 0; i < tenors.size(); i++) {
        std::cout << tenors[i] << ": " << rates[i] << std::endl;
    }
    std::cout << std::endl;
}

void RateCurve::addRate(Date tenor, double rate) {
    // Check if the tenor already exists and update if necessary
    for (size_t i = 0; i < tenors.size(); ++i) {
        if (tenors[i] == tenor) {
            rates[i] = rate;
            return;
        }
    }
    tenors.push_back(tenor);
    rates.push_back(rate);
}

double RateCurve::getRate(Date tenor) const {
    if (tenors.empty()) return 0.0;

    auto it = std::lower_bound(tenors.begin(), tenors.end(), tenor, [](const Date& d1, const Date& d2) {
        return d1 - d2 < 0;
    });

    if (it == tenors.end()) {
        return rates.back();
    } else if (it == tenors.begin()) {
        return rates.front();
    } else {
        size_t idx = std::distance(tenors.begin(), it);
        double t1 = tenors[idx - 1] - tenors[0];
        double t2 = tenors[idx] - tenors[0];
        double r1 = rates[idx - 1];
        double r2 = rates[idx];
        double t = tenor - tenors[0];
        return r1 + (r2 - r1) * (t - t1) / (t2 - t1);
    }
}

// Implementation of VolCurve member functions
void VolCurve::display() const {
    std::cout << "vol curve: " << name << std::endl;
    for (size_t i = 0; i < tenors.size(); i++) {
        std::cout << tenors[i] << ": " << vols[i] << std::endl;
    }
    std::cout << std::endl;
}

void VolCurve::addVol(Date tenor, double vol) {
    // Check if the tenor already exists and update if necessary
    for (size_t i = 0; i < tenors.size(); ++i) {
        if (tenors[i] == tenor) {
            vols[i] = vol;
            return;
        }
    }
    tenors.push_back(tenor);
    vols.push_back(vol);
}

double VolCurve::getVol(Date tenor) const {
    if (tenors.empty()) return 0.0;

    auto it = std::lower_bound(tenors.begin(), tenors.end(), tenor, [](const Date& d1, const Date& d2) {
        return d1 - d2 < 0;
    });

    if (it == tenors.end()) {
        return vols.back();
    } else if (it == tenors.begin()) {
        return vols.front();
    } else {
        size_t idx = std::distance(tenors.begin(), it);
        double t1 = tenors[idx - 1] - tenors[0];
        double t2 = tenors[idx] - tenors[0];
        double v1 = vols[idx - 1];
        double v2 = vols[idx];
        double t = tenor - tenors[0];
        return v1 + (v2 - v1) * (t - t1) / (t2 - t1);
    }
}
