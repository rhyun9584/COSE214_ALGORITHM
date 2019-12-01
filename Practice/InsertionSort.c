#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertionSort(int arr[], int count){
    for(int i = 1; i < count; i++){
        for(int j = i - 1; j >= 0; j--){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            else
            {
                break;
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

    InsertionSort(arr, num);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}