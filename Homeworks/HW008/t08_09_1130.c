#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compare(int num_a, int num_b){
    // is a < b
    int a_clone = num_a;
    int b_clone = num_b;

    int a_sum = 0;
    int b_sum = 0;

    while(a_clone > 0){
        a_sum += a_clone % 10;
        a_clone /= 10;
    }

    while(b_clone > 0){
        b_sum += b_clone % 10;
        b_clone /= 10;
    }

    if (a_sum < b_sum){
        return 1;
    } else if (a_sum > b_sum ){
        return 0;
    } else {
        char a_str[32], b_str[32];
        sprintf(a_str, "%d", num_a);
        sprintf(b_str, "%d", num_b);
        return (strcmp(a_str, b_str) < 0);
    }
}


void sort(int* arr, int begin, int end){
        int l = begin;
        int r = end;

        if (l >= r) return;

        int pivot = arr[l + (r - l) / 2];

        while(1){

            while (compare(arr[l], pivot))
                l++;

            while (compare(pivot, arr[r]))
                r--;

            if (l >= r)
                break;

            int buffer = arr[l];
            arr[l] = arr[r];
            arr[r] = buffer;

            l++;
            r--;
        }

        sort(arr, begin, r);
        sort(arr, r+1, end);
}



int main(){
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    int* arr = (int*)malloc(n*sizeof(int));

    for (int i = 1; i <= n; i++)
        arr[i - 1] = i;

    sort(arr, 0, n -1);
    for (int i = 0; i < n; i++){
        if (arr[i] == k){
            printf("%d\n", i+1);
        }
    }

    printf("%d\n", arr[k-1]);

    free(arr);
}