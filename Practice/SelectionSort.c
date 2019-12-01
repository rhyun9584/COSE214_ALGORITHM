#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findMin(int arr[], int start, int count){
    int minIndex = start;

    for(int i = start; i < count; i++){
        if(arr[minIndex] > arr[i]){
            minIndex = i;
        }
    }

    return minIndex;
}

void SelectionSort(int arr[], int count){
    for(int i = 0; i < count - 1; i++){
        int minIndex = findMin(arr, i, count);

        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
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

    SelectionSort(arr, num);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}