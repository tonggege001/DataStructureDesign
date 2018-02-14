#include <cmath>
bool isPrime(int M){
    for(int i = 2;i<sqrt(M);i++){
        if(M%i==0) return false;
    }
    return true;
}
int MinPrime(int N){
    for(int i = N;i>1;i--){
        if(isPrime(i)) return i;
    }
    return 1;
}
