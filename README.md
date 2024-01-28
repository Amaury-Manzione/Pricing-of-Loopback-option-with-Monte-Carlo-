# Pricing d'options loopback avec la méthode de Monte-Carlo

Nous calculons le prix ainsi que les différentes lettres grecques d'options loopback, dont le pay-off est de la forme un pay-off :

```math
$S(T) - \min_{t \in [0,T]} S_t$
```
pour un put

$$
\max_{t \in [0,T]} S_t - S(T)
$$
pour un put

Pour utiliser l'interface :
### _Sous Visual Code_ 

* Générer le fichier dll  : Générer -> Générer la solution
* ouvrir l'interface excel
