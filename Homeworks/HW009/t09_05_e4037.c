#include <stdio.h>
#include <stdlib.h>




typedef struct robot{
    int first;
    int second;
}robot;


robot* copy_arr(robot* arr_to_copy,int begin, int end){
    robot* copy = (robot*)malloc((end-begin)*sizeof(robot));
    int j = 0;
    for (int i = begin; i < end; i++){
        copy[j++] = arr_to_copy[i];
    }
    return copy;
}

robot* merge(robot* a, robot* b, int s_a, int s_b){
    robot* merged = (robot*) malloc((s_a + s_b)*sizeof(robot));
    int i=0, j= 0, k= 0;

    while (i < s_a && j < s_b) {
        if (a[i].first <= b[j].first) {
            merged[k++] = a[i++];
        } else {
            merged[k++] = b[j++];
        }
    }


    while(i < s_a){
        merged[k++] = a[i++];
    }

    while(j < s_b){
        merged[k++] = b[j++];
    }

    free(a);
    free(b);

    return merged;
}



robot* merge_sort(robot* arr, int size){

    if (size == 1||size == 0)
        return arr;

    int m = size / 2;

    robot* left = copy_arr(arr, 0, m);
    robot* right = copy_arr(arr, m, size);

    left = merge_sort(left, m);
    right = merge_sort(right, size - m);



    return merge(left, right, m, size - m);



}


int main(){
    int n;
    scanf("%d", &n);

    robot* robots = (robot*)malloc(n*sizeof(robot));

    for (int i = 0; i < n; i++){
        scanf("%d %d", &robots[i].first, &robots[i].second);
    }

    robots = merge_sort(robots, n);

    for(int i = 0; i < n; i++){
        printf("%d %d\n", robots[i].first, robots[i].second);
    }



    free(robots);
}



