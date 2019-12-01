#include <stdio.h>

int MoveHanoi(int n){
    if(n == 1)
        return 1;

    return MoveHanoi(n - 1) * 2 + 1;
}

int main(){
    int height;

    printf("Height of Hanoi >> ");
    scanf("%d", &height);

    printf("Move %d\n", MoveHanoi(height));
}