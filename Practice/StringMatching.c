#include <stdio.h>
#include <string.h>

int StringMatching(char arr[], char key[]){//found 1, not found 0
    int arrlen = strlen(arr);
    int keylen = strlen(key);

    for(int i = 0; i < arrlen - keylen + 1; i++){
        for(int j = 0; j < keylen; j++){
            if(arr[i+j] != key[j])
                break;

            if(j == keylen - 1)
                return 1;
        }
    }

    return 0;
}

int main(){
    char arr[20];
    char key[5];
    
    scanf("%s", arr);
    scanf("%s", key);

    int rst = StringMatching(arr, key);

    if(rst)
        printf("Find!\n");
    else
        printf("Not Found\n");
}