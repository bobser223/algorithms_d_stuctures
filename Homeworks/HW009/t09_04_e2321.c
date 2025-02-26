#include <stdio.h>
#include <stdlib.h>

void q_sort(int* arr, int begin, int end){
    if (begin >= end) return;

    int l = begin;
    int r = end;
    int pivot = arr[l + (r - l) / 2];

    while(1){

        while(arr[l] < pivot) l++;

        while(arr[r] > pivot) r--;

        if (l >= r) break;

        int buff = arr[l];

        arr[l] = arr[r];
        arr[r] = buff;

        l++;
        r--;
    }
    q_sort(arr, begin, r);
    q_sort(arr, r+1, end);
}



int main(){
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(n*sizeof(int));


    for (int i = 0; i < n; i++){
        scanf("%d", &(arr[i]));
    }

    q_sort(arr, 0, n-1);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    free(arr);
}
