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
/**
 * @brief Value2Hash 将整数映射到哈希表
 * @param prime 素数
 * @param max 最大值
 * @param value 数值
 * @param array 数组基地址
 * @return 哈希表
 */
int Value2Hash(int prime,int max,int value,int * array){
    while(value<0) value+=prime;//让值为正数
    value = value%prime;//映射到0-prime-1
    //寻找空位
    while(array[value]!=-1){
        value++;
        value%=prime;
    }
    return value;
}
