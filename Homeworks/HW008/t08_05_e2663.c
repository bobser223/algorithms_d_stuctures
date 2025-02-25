
#include <stdio.h>
#include <stdlib.h>




int bubble_sort(int* arr, int arr_size){
    int counter = 0;
    for (int j = arr_size - 1; j > 0; j-- ){
        int swap = 0;
        for (int i = 0; i < j; i++){
            if (arr[i] > arr[i+1]){
                int buffer = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = buffer;
                counter ++;
                swap = 1;
            }
        }
        if (!swap){
            return counter;
        }
    }
    return counter;
}


int main(){
    int size;
    scanf("%d", &size);

    int* arr = (int*)malloc(size*sizeof(int));

    for (int i = 0; i < size; i++){
        scanf("%d", &arr[i]);
    }

    printf("%d", bubble_sort(arr, size));

    free(arr);
}




