#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Merge(int arr[], int left, int middle, int right){
    int temp[right];

    int p = left; // first index of left arr
    int q = middle + 1; // first index of right arr
    int r = left; //firt empty index of new arr

    while(p <= middle && q <= right){
        if(arr[p] <= arr[q])
            temp[r++] = arr[p++];
        else
            temp[r++] = arr[q++];
    }

    while(p <= middle){
        temp[r++] = arr[p++];
    }
    while(q <= right){
        temp[r++] = arr[q++];
    }

    for(int i = left; i <= right; i++){
        arr[i] = temp[i];
    }
}

void MergeSort(int arr[], int left, int right){ // left is first index of left arr, right is last index of right arr
    if(left < right){
        int middle = (left + right) / 2;

        MergeSort(arr, left, middle);
        MergeSort(arr, middle + 1, right);
        Merge(arr, left, middle, right);
    }
}

void main(){
    int num = 6;
    int arr[num];

    srand(time(NULL));
    for(int i = 0; i < num; i++){
        arr[i] = rand() % 100 + 1; //1 ~ 100
    }

    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    MergeSort(arr, 0, num - 1);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");    
}