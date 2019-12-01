#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int arr[], int count){
    for(int i = count - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
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

    BubbleSort(arr, num);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}