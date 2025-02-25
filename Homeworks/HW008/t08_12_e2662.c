#include <stdio.h>
#include <stdlib.h>

int selection_sort(int *arr, int n) {
    int counter = 0;
    int pos = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        if (min_index != i) {

            if (i == pos || min_index == pos) {
                counter++;

                if (i == pos)
                    pos = min_index;
                else if (min_index == pos)
                    pos = i;
            }
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
    return counter;
}

int main(){
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    printf("%d", selection_sort(arr, n));
    free(arr);
    return 0;
}
