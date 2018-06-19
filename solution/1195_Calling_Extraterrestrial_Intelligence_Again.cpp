#include<stdio.h>
#include<vector>
#include<bitset>
#define ll long long

using namespace std;

vector<ll> get_prime(ll pmax){ // get vector of prime number until sqrt(pmax)
    bitset<10000001> P;
    vector<ll> premiers;
    P.set(); // initialisation
    P[0] = P[1] = 0;
    for (ll i = 2; i < pmax; i++){
        if(P[i]){
            for(ll j=i*i; j < pmax; j+=i)
                P[j]=0;
            premiers.push_back(i);
        }
    }
    return premiers;
}


int main(){
    ll m,a,b,p,q;
    
    while(scanf("%lld %lld %lld", &m, &a, &b) == 3 && (m + a + b)){
        p = 0; q = 0;
        vector<ll> prime = get_prime(m);
        
        for(int i = 0; i < prime.size(); i++){
            for(int j = i; j < prime.size(); j++){
                if(prime[i] * prime[j] > m) break;
                if((prime[j] * a <= prime[i] * b) && (prime[i] * prime[j] >= p * q)){
                    p = prime[i];
                    q = prime[j];
                }
            }
        }
        
        printf("%lld %lld\n", p, q);
    }
    
    return 0;
}
