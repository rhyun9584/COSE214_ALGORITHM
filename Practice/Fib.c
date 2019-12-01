#include <stdio.h>

int Fibonacci (int n){
    if(n <= 1)
        return n;

    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main(){
    int num;

    printf("n번째 피보나치 수열 구하기 >> ");
    scanf("%d", &num);

    printf("결과 : %d", Fibonacci(num));

    return 0;
}