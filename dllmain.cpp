// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include "BlackScholes.h"
#include "Lookback.h"
#include <iostream>

#define DLL_EXPORT __declspec(dllexport)


extern "C" {
    DLL_EXPORT double pricer_VBA(double S0,double r, double sigma,double T,double T0,int K,int n,int N) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, T0, K,n,N).getPrice();
    }

    DLL_EXPORT double delta_VBA(double S0, double r, double sigma, double T, double T0, int K, int n, int N,double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, T0, K, n, N).delta(epsilon);
    }

    DLL_EXPORT double gamma_VBA(double S0, double r, double sigma, double T, double T0, int K, int n, int N, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, T0, K, n, N).gamma(epsilon);
    }

    DLL_EXPORT double theta_VBA(double S0, double r, double sigma, double T, double T0, int K, int n, int N, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, T0, K, n, N).theta(epsilon);
    }

    DLL_EXPORT double rho_VBA(double S0, double r, double sigma, double T, double T0, int K, int n, int N, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, T0, K, n, N).rho(epsilon);
    }

    DLL_EXPORT double vega_VBA(double S0, double r, double sigma, double T, double T0, int K, int n, int N, double epsilon) {
        BlackScholes B(S0, r, sigma);
        return Lookback(B, T, T0, K, n, N).vega(epsilon);
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

