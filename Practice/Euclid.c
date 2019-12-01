#include <stdio.h>

int GCD(int a, int b){
    if(b == 0)
        return a;
    
    return GCD(b, a % b);
}

void main(){
    int num1, num2;
    int rst;

    scanf("%d %d", &num1, &num2);
    
    if(num1 > num2)
        rst = GCD(num1, num2);
    else
        rst = GCD(num2, num1);

    printf("%d & %d GCD : %d\n", num1, num2, rst);

}