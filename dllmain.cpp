// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include "BlackScholes.h"
#include "Lookback.h"
#include <iostream>

#define DLL_EXPORT __declspec(dllexport)


extern "C" {
    // Function to create a Lookback object
    DLL_EXPORT Lookback* CreateLookback_VBA(double S0, double r, double sigma, double T, int K, int N_path, int n) {
        try {
            BlackScholes blackScholes(S0, r, sigma);
            Lookback* lookback = new Lookback(blackScholes, T, K, N_path, n);
            return lookback;
        }
        catch (const std::exception& e) {
            std::cerr << "Error creating Lookback: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // Function to delete a Lookback object
    DLL_EXPORT void DeleteLookback_VBA(Lookback* lookback) {
        delete lookback;
    }

    DLL_EXPORT double price_VBA(Lookback* lookback) {
        std::vector<std::vector<double>> matrix = Lookback::generate_normal_increments(lookback->getN(),lookback->getn());
        return lookback->price(matrix);
    }

    DLL_EXPORT double delta_VBA(Lookback* lookback, double epsilon) {
        return lookback->delta(epsilon);
    }

    DLL_EXPORT double gamma_VBA(Lookback* lookback, double epsilon) {
        return lookback->gamma(epsilon);
    }

    DLL_EXPORT double theta_VBA(Lookback* lookback, double epsilon) {
        return lookback->theta(epsilon);
    }

    DLL_EXPORT double rho_VBA(Lookback* lookback, double epsilon) {
        return lookback->rho(epsilon);
    }

    DLL_EXPORT double vega_VBA(Lookback* lookback, double epsilon) {
        return lookback->vega(epsilon);
    }

    // functions that will be used to approximate price and greeks without explicitely building the lookback option

    DLL_EXPORT double compute_price(double S0, double r, double sigma, double T, int K, int N, int n) {
        BlackScholes B(S0, r, sigma);
        std::vector<std::vector<double>> matrix = Lookback::generate_normal_increments(N,n);
        return Lookback(B, T, K, N, n).price(matrix);
    }

    DLL_EXPORT double compute_delta(double S0, double r, double sigma, double T, int K, int N, int n, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, K, N, n).delta(epsilon);
    }

    DLL_EXPORT double compute_gamma(double S0, double r, double sigma, double T, int K, int N, int n, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, K, N, n).gamma(epsilon);
    }

    DLL_EXPORT double compute_theta(double S0, double r, double sigma, double T, int K, int N, int n, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, K, N, n).theta(epsilon);
    }

    DLL_EXPORT double compute_rho(double S0, double r, double sigma, double T, int K, int N, int n, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, K, N, n).rho(epsilon);
    }

    DLL_EXPORT double compute_vega(double S0, double r, double sigma, double T, int K, int N, int n, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, K, N, n).vega(epsilon);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

