
#ifndef PROJET_LOOKBACK_H
#define PROJET_LOOKBACK_H

#include "BlackScholes.h"
#include <cmath>

/**
 * @brief This class represents a lookback option
 * 
 */
class Lookback {

private:
    // the underlying asset
    BlackScholes S_;
    // maturity
    double T_;
    // initial date
    double T0_;
    // type of option (call or put)
    int K_;
    // number of paths for the approximation via Monte Carlo
    int N_;
    // number of sub intervals for each discretization
    int n_;

    // the approximative price of the option
    double price_;

public:
    /**
     * @brief Construct a new Loopback object
     * 
     * @throw "Invalid argument" if : T, T0, N or n negative, T0 > T, K different from 0 and 1
     * 
     * @param S the underlying
     * @param T the maturity
     * @param T0 the initial date
     * @param K the type (0 for call and 1 for put)
     * @param N number of paths for the approximation via Monte Carlo
     * @param n number of sub intervals for each discretization
     */
    Lookback(const BlackScholes &S, double T, double T0, int K, int N, int n);

    /**
     * @brief Get the underlying
     * 
     * @return the underlying
     */
    const BlackScholes &getS() const;

    /**
     * @brief Get the maturity 
     * 
     * @return The maturity
     */
    int getT() const;

    /**
     * @brief Get the initial date
     * 
     * @return the initial date
     */
    int getT0() const;

    /**
     * @brief Get the type
     * 
     * @return int representing the type
     */
    int getK() const;

    /**
     * @brief Get the approximative price 
     * 
     * @return double 
     */
    double getPrice() const;

    /**
     * @brief Get N
     * 
     * @return int 
     */
    int getN() const;

    /**
     * @brief Get n
     * 
     * @return int 
     */
    int getn() const;

private:
    /**
     * @brief Approximation of the price via Monte Carlo method
     * 
     * @param S the underlying asset
     * @param T maturity
     * @param T0 initial date
     * @param K type 
     * @param N number of paths
     * @param n number of sub intervals
     * @return The approximated price
     */
    double pricer(BlackScholes S, double T, double T0, int K, int N, int n) const;

public:
    /**
     * @brief Get the delta 
     * 
     * @throw "Invalid argument" if epsilon =< 0
     *  
     * @param epsilon the small variation
     * @return the approximation of the delta
     */
    double delta(double epsilon) const;

    /**
     * @brief Get the gamma
     * 
     * @throw "Invalid argument" if epsilon =< 0
     *  
     * @param epsilon the small variation
     * @return the approximation of the gamma
     */
    double gamma(double epsilon) const;

    /**
     * @brief Get the theta
     * 
     * @throw "Invalid argument" if epsilon =< 0
     *  
     * @param epsilon the small variation
     * @return the approximation of the theta
     */
    double theta(double epsilon) const;

    /**
     * @brief Get the rho
     * 
     * @throw "Invalid argument" if epsilon =< 0
     *  
     * @param epsilon the small variation
     * @return the approximation of the rho
     */
    double rho(double epsilon) const;

    /**
     * @brief Get the vega
     * 
     * @throw "Invalid argument" if epsilon =< 0
     *  
     * @param epsilon the small variation
     * @return the approximation of the vega
     */
    double vega(double epsilon) const;
};

#endif