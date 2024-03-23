# Pricing of Lookback Options with Monte Carlo method under Black & Scholes model

In this project we approximate the price and greeks of Lookback options, which have the following pay-offs :

$$
S(T) - \min_{t \in [0,T]} S_t
\quad
,
\quad
\max_{t \in [0,T]} S_t - S(T)
$$

for a call and a put respectively.


To use the interface :
## _Visual Code_ 

* To generate the dll file  : Open Dll1.sln -> Build -> Build Solution (Générer -> Générer la solution)
* Open Excel interface. 

## _Excel interface_

You have two choices. 

### First possibility
The first one is to use the second line of the interface. You have to fill information about the option you want to study : 

- $S_0$ is the price of the underlying share at the present date
- $r$ is the constant risk-free yield
- sigma the volatility of the underlying
- $T$ is the residual maturity in years
- $T_0$ is the present date, 0 by default
- $K$ indicates the type of the option : 0 for a call, 1 for a put
- $N$ is the number of paths used in the Monte Carlo method
- $n$ is the number of discretization points used to simulate each path

Then you can save this information by pressing "Save Changes". The approximation of the price of the option will immediately appear in cell $B4$

Then in cell $F4$, you can set the small value of $\epsilon$ that will be used to approximate the greeks of the option. For example, the delta will be approximated by 

$$\frac{Price^{Monte Carlo}(S_0 + \epsilon, r, \sigma, T, T_0, K, N, n) - Price^{Monte Carlo}(S_0 - \epsilon, r, \sigma, T, T_0, K, N, n)}{2\epsilon}$$

You can then generate approximations for delta, gamma, theta, rho and vega by clicking on the associated buttons.

Moreover, you can generate two plots : 

- A plot of the option price, as a function of the price of the underlying share at computation date $T_0$.

- A plot of the option delta as a function of the price of the underlying share at computation date $T_0$.

For both on these plots, you will have to fill :

- $S_0\space{}min$ is the minimum value of $S_0$ on the graph
- $S_0\space{}max$ is the maximum value of $S_0$ on the graph
- $N$ is the number of paths used to approximate the price of each option for each value of $S_0$ (not used for the delta plot)
- $n$ the number of discretization points used to approximate each option price/delta for each value of $S_0$
- $number\space{}of\space{}points$ is the number of desired points on the plot.
- $\epsilon$ is the value of epsilon used to approximate each delta for each value of $S_0$.

You can then generate both graphs by clicking on the associated buttons.

### Second possibility

You can directly approximate the price and greeks of a Lookback option by using the following functions : 

- For the price : GetPrice($S_0, r, \sigma, T, T_0, K, N, n$)
- For the greeks : GetGreek (for example GetDelta) ($S_0, r, \sigma, T, T_0, K, N, n, \epsilon$)

Where $S_0, r, \sigma, T, T_0, K, N, n, \epsilon$ are defined in the first part.
