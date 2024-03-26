
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
    // residual maturity in years (assume the option begins at T0 = 0)
    double T_;
    // type of option (call or put)
    int K_;
    // number of paths for the approximation via Monte Carlo
    int N_;
    // number of sub intervals for each discretization
    int n_;

public:
    /**
     * @brief Construct a new Loopback object
     * 
     * @throw "Invalid argument" if : T, N or n negative, K different from 0 and 1
     * 
     * @param S the underlying
     * @param T the residual maturity
     * @param K the type (0 for call and 1 for put)
     * @param N number of paths for the approximation via Monte Carlo
     * @param n number of sub intervals for each discretization
     */
    Lookback(const BlackScholes &S, double T, int K, int N, int n);

    /**
     * @brief Get the underlying
     * 
     * @return the underlying
     */
    const BlackScholes &getS() const;

    /**
     * @brief Get the residual maturity 
     * 
     * @return The residual maturity
     */
    double getT() const;

    /**
     * @brief Get the type
     * 
     * @return int representing the type
     */
    int getK() const;

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

    /**
     * @brief generate matrix of centred normal laws
     * 
     * @param N 
     * @param n 
     * @return std::vector<std::vector<double>> 
     */
    static std::vector<std::vector<double>> generate_normal_increments(int N,int n);

    /**
     * @brief Approximation of the price via Monte Carlo method
     *
     * 
     * @return The approximated price
     */
    double price(std::vector<std::vector<double>>) const;

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