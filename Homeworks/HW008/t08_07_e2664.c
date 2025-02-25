#include <stdio.h>
#include <stdlib.h>


void print_arr(int* arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int* arr, int size){
    for (int i = 1; i < size; i++){
        int pos = i;
        int curr_el = arr[i];

        while(pos > 0){
            if (arr[pos - 1] > curr_el){
                arr[pos] = arr[pos-1];
            } else{
                break;
            }
            pos--;
        }

        if (pos != i) {
            arr[pos] = curr_el;
            print_arr(arr, size);
        }
    }
}



int main(){
    int n;
    scanf("%d", &n);

    int* arr = (int *)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    insertion_sort(arr, n);

    free(arr);

}