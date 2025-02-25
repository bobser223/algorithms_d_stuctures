#include <stdio.h>
#include <stdlib.h>



int compare(int a, int b){
    // a < b

    int a_last = a % 10;
    int b_last = b % 10;

    if (a_last == b_last){
        return a < b;
    }

    return a_last < b_last;


}

void q_sort(int* arr, int begin, int end){
    int l = begin;
    int r = end;

    if(l >= r) return;

    int pivot = arr[l + (r-l) /2 ];

    while(1){
        while(compare(arr[l], pivot))
            l++;

        while (compare(pivot, arr[r]))
            r--;

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
        scanf("%d", &arr[i]);
    }

    q_sort(arr, 0, n-1);

    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }

    free(arr);
}