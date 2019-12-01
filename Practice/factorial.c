#include <stdio.h>

int factorial(int n){
    if(n == 0)
        return 1;
    
    return n * factorial(n - 1);
}

int main(){
    int num;

    printf("n의 Factorial 구하기 >> ");
    scanf("%d", &num);

    printf("result : %d\n", factorial(num));
}