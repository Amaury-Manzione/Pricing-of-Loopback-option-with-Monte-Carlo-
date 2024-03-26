#include "Lookback.h"

Lookback::Lookback(const BlackScholes &S, double T, int K, int N, int n) : S_(S), T_(T), K_(K), N_(N), n_(n) {
    if (T < 0 || N <= 0 || n <= 0){
        throw std::invalid_argument("T, N, n must be positive");
    }

    if (K != 0 && K != 1){
        throw std::invalid_argument("The type K must be equal to 0 or 1");
    }
}

const BlackScholes &Lookback::getS() const {
    return S_;
}

double Lookback::getT() const {
    return T_;
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

std::vector<std::vector<double>> Lookback::generate_normal_increments(int N, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    std::vector<std::vector<double>> matrix(N, std::vector<double>(n));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = distribution(gen);
        }
    }

    return matrix;
}

double Lookback::price(std::vector<std::vector<double>> matrix) const
{
    double step = double(T_/n_);
    double price_approx = 0;
    for (int i = 0; i < N_; i++) {
        price_approx += S_.payoff_lookback_one_path(step, n_, K_,matrix[i]);
    }

    // discounting 
    return exp(-S_.getR() * T_) * price_approx / N_;
}

double Lookback::delta(double epsilon) const {

    std::vector<std::vector<double>> matrix = generate_normal_increments(N_,n_);

    // Compute option price at S - epsilon
    double S_minus_epsilon = S_.getS0() - epsilon;
    BlackScholes S_left(S_minus_epsilon, S_.getR(), S_.getSigma());
    double P_left = Lookback(S_left, T_, K_, N_, n_).price(matrix);

    // Compute option price at S + epsilon
    double S_plus_epsilon = S_.getS0() + epsilon;
    BlackScholes S_right(S_plus_epsilon, S_.getR(), S_.getSigma());
    double P_right = Lookback(S_right, T_, K_, N_, n_).price(matrix);

    // Compute delta using centered difference
    double delta = (P_right - P_left) / (2 * epsilon);

    return delta;
}

double Lookback::gamma(double epsilon) const{
    std::vector<std::vector<double>> matrix = generate_normal_increments(N_,n_);

    // Compute option price at S - epsilon
    double S_minus_epsilon = S_.getS0() - epsilon;
    BlackScholes S_left(S_minus_epsilon, S_.getR(), S_.getSigma());
    double P_left = Lookback(S_left, T_, K_, N_, n_).price(matrix);

    // Compute option price at S + epsilon
    double S_plus_epsilon = S_.getS0() + epsilon;
    BlackScholes S_right(S_plus_epsilon, S_.getR(), S_.getSigma());
    double P_right = Lookback(S_right, T_, K_, N_, n_).price(matrix);

    // Compute gamma using centered difference
    double gamma = (P_right - 2 * this->price(matrix) + P_left) / (epsilon * epsilon);

    return gamma;
}

double Lookback::theta(double epsilon) const{
    std::vector<std::vector<double>> matrix = generate_normal_increments(N_,n_);

    // Compute option price at T - epsilon
    double P_minus_epsilon = Lookback(S_, T_ - epsilon, K_, N_, n_).price(matrix);

    // Compute option price at T + epsilon
    double P_plus_epsilon = Lookback(S_, T_ + epsilon, K_, N_, n_).price(matrix);

    // Compute theta using centered difference
    double theta = (P_plus_epsilon - P_minus_epsilon) / (2 * epsilon);

    return theta;
}

double Lookback::rho(double epsilon) const{
    std::vector<std::vector<double>> matrix = generate_normal_increments(N_,n_);

    // Compute option price at r - epsilon
    double r_minus_epsilon = S_.getR() - epsilon;
    BlackScholes S_left(S_.getS0(), r_minus_epsilon, S_.getSigma());
    double P_left = Lookback(S_left, T_, K_, N_, n_).price(matrix);

    // Compute option price at r + epsilon
    double r_plus_epsilon = S_.getR() + epsilon;
    BlackScholes S_right(S_.getS0(), r_plus_epsilon, S_.getSigma());
    double P_right = Lookback(S_right, T_, K_, N_, n_).price(matrix);

    // Compute rho using centered difference
    double rho = (P_right - P_left) / (2 * epsilon);

    return rho;

}

double Lookback::vega(double epsilon) const{
    std::vector<std::vector<double>> matrix = generate_normal_increments(N_,n_);

    // Compute option price at sigma - epsilon
    double sigma_minus_epsilon = S_.getSigma() - epsilon;
    BlackScholes S_left(S_.getS0(), S_.getR(), sigma_minus_epsilon);
    double P_left = Lookback(S_left, T_, K_, N_, n_).price(matrix);

    // Compute option price at S + epsilon
    double sigma_plus_epsilon = S_.getSigma() + epsilon;
    BlackScholes S_right(S_.getS0(), S_.getR(), sigma_plus_epsilon);
    double P_right = Lookback(S_right, T_, K_, N_, n_).price(matrix);

    // Compute vega using centered difference
    double vega = (P_right - P_left) / (2 * epsilon);

    return vega;
};