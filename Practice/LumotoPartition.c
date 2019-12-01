#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int LumotoPartition(int arr[], int left, int right){
    int pivot = arr[left];
    int s = left;

    for(int i = s + 1; i <= right; i++){
        if(pivot > arr[i]){
            s++;
            swap(&arr[s], &arr[i]);
        }
    }

    swap(&arr[s], &arr[left]);
    return s;
}

void InsertionSort(int arr[], int count){
    for(int i = 1; i < count; i++){
        for(int j = i - 1; j >= 0; j--){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    int num = 30;
    int key;
    int arr[num];

    srand(time(NULL));
    for(int i = 0; i < num; i++){
        arr[i] = rand() % 100 + 1; //1 ~ 100
    }

    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("kth smallest number >> k = ");
    scanf("%d", &key);

    int pivotIndex = LumotoPartition(arr, 0, num - 1);

    if(pivotIndex != key - 1){
        do{
            if(pivotIndex < key - 1)
                pivotIndex = LumotoPartition(arr, pivotIndex + 1, num - 1);
            else
                pivotIndex = LumotoPartition(arr, 0, pivotIndex - 1);

            //printf("%d\n", pivotIndex);
        }while(pivotIndex != key - 1);
    }

    printf("%d is %d th smallest number\n", arr[pivotIndex], key);

    InsertionSort(arr, num);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
/*
    //after partitioning
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
*/
}