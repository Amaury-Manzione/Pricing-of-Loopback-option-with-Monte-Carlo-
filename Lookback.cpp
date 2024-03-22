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
}

const BlackScholes &Lookback::getS() const {
    return S_;
}

double Lookback::getT() const {
    return T_;
}

double Lookback::getT0() const {
    return T0_;
}

int Lookback::getK() const {
    return K_;
}

int Lookback::getn() const{
    return n_;
}

int Lookback::getN() const{
    return N_;
}

double Lookback::price() const{
    double step = double(T_ - T0_)/n_;
    double price_approx = 0;
    for (int i = 0; i < N_; i++) {
        price_approx += S_.payoff_lookback_one_path(step, n_, K_).first;
    }

    // discounting 
    return exp(-S_.getR() * T_) * price_approx / N_;
}

double Lookback::delta_IBP() const{
    double step = double(T_ - T0_)/n_;
    double delta_approx = 0;
    for (int i = 0; i < N_; i++) {
        std::pair<double,double> p = S_.payoff_lookback_one_path(step, n_, K_);
        delta_approx += p.first*p.second / (T_*getS().getSigma()*getS().getS0());
    }

    // discounting 
    return exp(-S_.getR() * T_) * delta_approx / N_;
}

double Lookback::delta(double epsilon) const {
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at S - epsilon
    double S_minus_epsilon = S_.getS0() - epsilon;
    BlackScholes S_left(S_minus_epsilon, S_.getR(), S_.getSigma());
    double P_left = Lookback(S_left, T_, T0_, K_, M, n_).price();

    // Compute option price at S + epsilon
    double S_plus_epsilon = S_.getS0() + epsilon;
    BlackScholes S_right(S_plus_epsilon, S_.getR(), S_.getSigma());
    double P_right = Lookback(S_right, T_, T0_, K_, M, n_).price();

    // Compute delta using centered difference
    double delta = (P_right - P_left) / (2 * epsilon);

    return delta;
}

double Lookback::gamma_IBP() const{
    double step = double(T_ - T0_)/n_;
    double gamma_approx = 0;
    for (int i = 0; i < N_; i++) {
        std::pair<double,double> p = S_.payoff_lookback_one_path(step, n_, K_);
        double sigma = getS().getSigma();
        double S0 = getS().getS0();
        gamma_approx += ((p.second*p.second)/(sigma*T_) -p.second -1/sigma)*p.first / (T_*sigma*S0*S0);
    }

    // discounting 
    return exp(-S_.getR() * T_) * gamma_approx / N_;
}

double Lookback::gamma(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at S - epsilon
    double S_minus_epsilon = S_.getS0() - epsilon;
    BlackScholes S_left(S_minus_epsilon, S_.getR(), S_.getSigma());
    double P_left = Lookback(S_left, T_, T0_, K_, M, n_).price();

    // Compute option price at S + epsilon
    double S_plus_epsilon = S_.getS0() + epsilon;
    BlackScholes S_right(S_plus_epsilon, S_.getR(), S_.getSigma());
    double P_right = Lookback(S_right, T_, T0_, K_, M, n_).price();

    // Compute gamma using centered difference
    double gamma = (P_right - 2 * this->price() + P_left) / (epsilon * epsilon);

    return gamma;
}

double Lookback::theta(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at T - epsilon
    double P_minus_epsilon = Lookback(S_, T_ - epsilon, T0_, K_, M, n_).price();

    // Compute option price at T + epsilon
    double P_plus_epsilon = Lookback(S_, T_ + epsilon, T0_, K_, M, n_).price();

    // Compute theta using centered difference
    double theta = (P_plus_epsilon - P_minus_epsilon) / (2 * epsilon);

    return theta;
}

double Lookback::rho(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at r - epsilon
    double r_minus_epsilon = S_.getR() - epsilon;
    BlackScholes S_left(S_.getS0(), r_minus_epsilon, S_.getSigma());
    double P_left = Lookback(S_left, T_, T0_, K_, M, n_).price();

    // Compute option price at r + epsilon
    double r_plus_epsilon = S_.getR() + epsilon;
    BlackScholes S_right(S_.getS0(), r_plus_epsilon, S_.getSigma());
    double P_right = Lookback(S_right, T_, T0_, K_, M, n_).price();

    // Compute rho using centered difference
    double rho = (P_right - P_left) / (2 * epsilon);

    return rho;

}

double Lookback::vega(double epsilon) const{
    int M = int(4 / std::pow(epsilon, 4));

    // Compute option price at sigma - epsilon
    double sigma_minus_epsilon = S_.getSigma() - epsilon;
    BlackScholes S_left(S_.getS0(), S_.getR(), sigma_minus_epsilon);
    double P_left = Lookback(S_left, T_, T0_, K_, M, n_).price();

    // Compute option price at S + epsilon
    double sigma_plus_epsilon = S_.getSigma() + epsilon;
    BlackScholes S_right(S_.getS0(), S_.getR(), sigma_plus_epsilon);
    double P_right = Lookback(S_right, T_, T0_, K_, M, n_).price();

    // Compute vega using centered difference
    double vega = (P_right - P_left) / (2 * epsilon);

    return vega;
};