#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//found 1, not found 0
int BinarySearch(int arr[], int left, int right, int key){
    if(left >= right){
        return 0;
    }

    int middle = (left + right) / 2;

    if(key == arr[middle]){
        return 1;
    }
    else if(key > arr[middle])
        return BinarySearch(arr, middle + 1, right, key);
    else
        return BinarySearch(arr, left, middle - 1, key);
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

    InsertionSort(arr, num);

    //after sorting
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("find >> ");
    scanf("%d", &key);

    if(BinarySearch(arr, 0, num - 1, key))
        printf("Found!\n");
    else
        printf("Not Found\n");
}