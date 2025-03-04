#include <stdio.h>
#include <stdlib.h>


void rec(int i, int currSum, int s, int N, int* arr, int* best) {
    if (*best == N) return;

    if (currSum > *best)
        *best = currSum;


    if (i >= s)
        return;

    rec(i + 1, currSum, s, N, arr, best);


    if (currSum + arr[i] <= N) {
        rec(i + 1, currSum + arr[i], s, N, arr, best);
    }
}

int max_time(int* arr, int s, int N) {
    int best = 0;
    rec(0, 0, s, N, arr, &best);
    return best;
}

int main(){
    FILE *file = fopen("input.txt", "r");

    int N, s;

    while (fscanf(file, "%d %d", &N, &s) == 2) {
        int* arr = (int*)malloc(s * sizeof(int));

        for (int i = 0; i < s; i++) {
            fscanf(file, "%d", &arr[i]);
        }

        printf("sum:%d\n", max_time(arr, s, N));
        free(arr);
    }

    fclose(file);
    return 0;
}
