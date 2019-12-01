#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int ClosestPair(int arr[], int count){
    int mindir = abs(arr[1] - arr[0]);
    int closestIndex = 0;

    for(int i = 1; i < count - 1; i++){
        int dir = abs(arr[i + 1] - arr[i]);

        if(dir < mindir){
            closestIndex = i;
            mindir = dir;
        }
    }

    return closestIndex;
}

int main(){
    int num = 20;
    int arr[num];

    srand(time(NULL));
    for(int i = 0; i < num; i++){
        arr[i] = rand() % 100 + 1; //1 ~ 100
    }

    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    int Index = ClosestPair(arr, num);

    printf("%d and %d are the closest pair\n", arr[Index], arr[Index + 1]);

    return 0;
}