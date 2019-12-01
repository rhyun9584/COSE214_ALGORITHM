#include <stdio.h>

int Multiple(int a, int b){
    if(a == 1)
        return b;
    
    if(a % 2){
        return Multiple(a / 2, b * 2) + b;
    }
    else{
        return Multiple(a / 2, b * 2);
    }
}

void main(){
    int num1, num2;
    scanf("%d %d", &num1, &num2);

    printf("result : %d\n", Multiple(num1, num2));
}