////
// Created by Amaury Manzione on 11/11/2023.
//

#ifndef PROJET_BLACKSCHOLES_H
#define PROJET_BLACKSCHOLES_H

#include <stdexcept>
#include <cmath>
#include <random>
#include <iostream>

/**
 * @brief This class represents an underlying asset under the Black and Scholes model
 *
 */
class BlackScholes {

private:
    // price of the underlying at initial date
    double S0_;
    // constant risk-free yield r
    double r_;
    // volatility
    double sigma_;

public:
    /**
     * @brief Construct a new asset
     *
     * @throws "Invalid argument" if sigma < 0
     *
     * @param S0 price of the underlying at initial date
     * @param r constant risk-free yield r
     * @param sigma volatility
    */
    BlackScholes(double S0, double r, double sigma);

    /**
     * @brief Get the price of the underlying at initial date
     *
     * @return the initial price
     */
    double getS0() const;

    /**
     * @brief Get the constant risk-free yield r
     *
     * @return constant risk-free yield r
     */
    double getR() const;

    /**
     * @brief Get the volatility
     *
     * @return the volatility
     */
    double getSigma() const;

    /**
     * @brief Given a step, n, and a type, generates a discrete path of the underlying asset
     * under the Black and Scholes model at the following dates :
     *
     * T0 (we observe S0 at this date)
     * T1 = T0 + step
     * ...
     * Tn = T0 + step * n
     *
     * Then returns S(Tn) - min(S(t)) over [T0; Tn] if type = 0
     * and max(S(t)) - S(Tn) over [T0; Tn] if type = 1
     *
     * @throws "Invalid argument" if step or n <= 0 and if type not equal to 0 or 1
     *
     * @param pas
     * @param n
     * @param type
     * @return the undiscounted payoff
     */
    double payoff_lookback_one_path(double step, double n, int type) const;
};


#endif //PROJET_BLACKSCHOLES_H
