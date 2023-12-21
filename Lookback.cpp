#include "Lookback.h"

Lookback::Lookback(const BlackScholes &S, double T, double T0, int K, int N, int n) : S_(S), T_(T), T0_(T0), K_(K), N_(N), n_(n) {
    if (T < 0 || T0 < 0 || N <= 0 || n <= 0){
        throw std::invalid_argument("T, T0, N, n must be positive");
    }

    if (K != 0 && K != 1){
        throw std::invalid_argument("The type K must be equal to 0 or 1");
    }

    if (T0 > T){
        throw std::invalid_argument("Initial must be before the maturity");
    }

    price_ = pricer(S, T, T0, K, N, n);
}

const BlackScholes &Lookback::getS() const {
    return S_;
}

int Lookback::getT() const {
    return T_;
}

int Lookback::getT0() const {
    return T0_;
}

int Lookback::getK() const {
    return K_;
}

double Lookback::getPrice() const{
    return price_;
}

int Lookback::getn() const{
    return n_;
}

int Lookback::getN() const{
    return N_;
}

double Lookback::pricer(BlackScholes S, double T, double T0, int K, int N, int n) const{
    double step = double(T - T0)/n;
    double price = 0;
    for (int i = 0; i < N; i++) {
        price += S.payoff_lookback_one_path(step, n, K);
    }

    // discounting 
    return exp(-S.getR() * T) * price / N;
}

double Lookback::delta(double epsilon) const {
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at S - epsilon
    double S_minus_epsilon = S_.getS0() - epsilon;
    BlackScholes S_left(S_minus_epsilon, S_.getR(), S_.getSigma());
    double P_left = pricer(S_left, T_, T0_, K_, M, n_);

    // Compute option price at S + epsilon
    double S_plus_epsilon = S_.getS0() + epsilon;
    BlackScholes S_right(S_plus_epsilon, S_.getR(), S_.getSigma());
    double P_right = pricer(S_right, T_, T0_, K_, M, n_);

    // Compute delta using centered difference
    double delta = (P_right - P_left) / (2 * epsilon);

    return delta;
}

double Lookback::gamma(double epsilon) const{
    int M = int(2 / std::pow(epsilon, 2));

    // Compute option price at S - epsilon
    double S_minus_epsilon = S_.getS0() - epsilon;
    BlackScholes S_left(S_minus_epsilon, S_.getR(), S_.getSigma());
    double P_left = pricer(S_left, T_, T0_, K_, M, n_);

    // Compute option price at S + epsilon
    double S_plus_epsilon = S_.getS0() + epsilon;
    BlackScholes S_right(S_plus_epsilon, S_.getR(), S_.getSigma());
    double P_right = pricer(S_right, T_, T0_, K_, M, n_);

    // Compute gamma using centered difference
    double gamma = (P_left - 2 * price_ + P_right) / (4 * epsilon * epsilon);

    return gamma;
}

double Lookback::theta(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at T - epsilon
    double P_minus_epsilon = pricer(S_, T_ - epsilon, T0_, K_, M, n_);

    // Compute option price at T + epsilon
    double P_plus_epsilon = pricer(S_, T_ + epsilon, T0_, K_, M, n_);

    // Compute theta using centered difference
    double theta = (P_plus_epsilon - P_minus_epsilon) / (2 * epsilon);

    return theta;
}

double Lookback::rho(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at r - epsilon
    double r_minus_epsilon = S_.getR() - epsilon;
    BlackScholes S_left(S_.getS0(), r_minus_epsilon, S_.getSigma());
    double P_left = pricer(S_left, T_, T0_, K_, M, n_);

    // Compute option price at r + epsilon
    double r_plus_epsilon = S_.getR() + epsilon;
    BlackScholes S_right(S_.getS0(), r_plus_epsilon, S_.getSigma());
    double P_right = pricer(S_right, T_, T0_, K_, M, n_);

    // Compute rho using centered difference
    double rho = (P_right - P_left) / (2 * epsilon);

    return rho;

}

double Lookback::vega(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at sigma - epsilon
    double vega_minus_epsilon = S_.getSigma() - epsilon;
    BlackScholes S_left(S_.getS0(), S_.getR(), vega_minus_epsilon);
    double P_left = pricer(S_left, T_, T0_, K_, M, n_);

    // Compute option price at S + epsilon
    double vega_plus_epsilon = S_.getSigma() + epsilon;
    BlackScholes S_right(S_.getS0(), S_.getR(), vega_plus_epsilon);
    double P_right = pricer(S_right, T_, T0_, K_, M, n_);

    // Compute vega using centered difference
    double vega = (P_right - P_left) / (2 * epsilon);

    return vega;
};