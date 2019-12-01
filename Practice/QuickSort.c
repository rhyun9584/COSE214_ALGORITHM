#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//return pivot's Index
int Partition(int arr[], int left, int right){
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while(i <= j){
        while(pivot >= arr[i] && i <= right){
            i++;
        }
        while(pivot <= arr[j] && j >= left + 1){
            j--;
        }

        if(i <= j){
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[left], &arr[j]);

    return j;
}

void QuickSort(int arr[], int left, int right){
    if(left < right){
        int s = Partition(arr, left, right);

        QuickSort(arr, left, s-1);
        QuickSort(arr, s+1, right);
    }
}

int main(){
    int num = 100;
    int arr[num];

    srand(time(NULL));
    for(int i = 0; i < num; i++){
        arr[i] = rand() % 100 + 1; //1 ~ 100
    }

    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    QuickSort(arr, 0, num - 1);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}