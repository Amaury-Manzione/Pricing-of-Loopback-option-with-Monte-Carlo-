////
// Created by Amaury Manzione on 11/11/2023.
//

#include "BlackScholes.h"

BlackScholes::BlackScholes(double S0, double r, double sigma) : S0_(S0), r_(r), sigma_(sigma) {
    if (sigma < 0) {
        throw std::invalid_argument("Sigma must be positive");
    }
}

double BlackScholes::getS0() const {
    return S0_;
}

double BlackScholes::getR() const {
    return r_;
}

double BlackScholes::getSigma() const {
    return sigma_;
}

double BlackScholes::payoff_lookback_one_path(double step, double n, int type) const {
    if (type != 0 && type != 1) {
        throw std::invalid_argument("Type must be 0 or 1");
    }

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Simulate the path using the Black and Scholes model
    double dt = step;
    double St = S0_;
    double minSt = S0_;  // Minimum value for lookback call
    double maxSt = S0_;  // Maximum value for lookback put

    for (int i = 0; i <= n; ++i) {
        double Z = distribution(gen);
        St = St * exp((r_ - 0.5 * sigma_ * sigma_) * dt + sigma_ * sqrt(dt) * Z);

        // Update minimum and maximum values for lookback options
        if (St < minSt)
            minSt = St;
        if (St > maxSt)
            maxSt = St;
    }

    // Calculate lookback payoff based on the option type
    if (type == 0) {  // Call option
        return St - minSt;
    }
    else {  // Put option
        return maxSt - St;
    }
}