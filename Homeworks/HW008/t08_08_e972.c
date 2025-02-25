#include <stdio.h>
#include <stdlib.h>

typedef long long ll;


void selection_sort(ll* arr, int size){
    for (int j = size - 1; j >0; j--) {
        int max_pos = 0;
        for (int i = 1; i < j + 1; i++) {
            if (arr[i] > arr[max_pos]){
                max_pos = i;
            }
        }
        ll buffer = arr[j];
        arr[j] = arr[max_pos];
        arr[max_pos] = buffer;
    }
}





int main(){
    int n;
    scanf("%d", &n);

    ll* arr = (ll*)malloc(n*sizeof(ll));

    ll h, m, s;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &h, &m, &s);
        arr[i] = h * 60 * 60 + m * 60 + s;
    }

    selection_sort(arr, n);

    for (int i = 0; i < n; i++) {
        ll h = arr[i] / 3600;
        ll m = (arr[i] % 3600) / 60;
        ll s = arr[i] % 60;
        printf("%lld %lld %lld\n", h, m, s);

    }

    free(arr);
}