#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int* arr, size_t size){
    printf("[ ");
    for(int i =0; i< size; i++)
        printf("%d, ", arr[i]);

    printf("]\n");
}


static void fill_arr(int* arr, size_t size){
    for (size_t i = 0; i < size; i++)
        arr[i] = rand() % size;

}

static void swap(int* arr, int first_position, int second_position){

    // the same as arr[first_position], arr[second_position] = arr[second_position], arr[first_position]

    int buffer = arr[first_position];

    arr[first_position] = arr[second_position];
    arr[second_position] = buffer;
}

int* quick_sort(int* arr_to_sort, int begin, int end){
    if (begin >= end) return arr_to_sort;

    int pivot = arr_to_sort[begin + (end - begin) / 2];

    int left = begin;
    int right = end;

    while (1){
        while (arr_to_sort[left] < pivot)
            left++;

        while (arr_to_sort[right] > pivot)
            right--;

        if (left >= right)
            break;

        swap(arr_to_sort, left, right);

        left++;
        right--;

    }

    quick_sort(arr_to_sort, begin, right);
    quick_sort(arr_to_sort, right+ 1, end);

    return arr_to_sort;
}

//int main(){
//    size_t arr_size = 1000000000;
//    int* arr_to_sort = (int*)calloc(arr_size, sizeof (int));
//
////    arr_to_sort[0] = 9;
////    arr_to_sort[1] = 10;
////    arr_to_sort[2] = 7;
////    arr_to_sort[3] = -1;
////    arr_to_sort[4] = 4;
////    arr_to_sort[5] = 3;
////    arr_to_sort[6] = 2;
//
//    fill_arr(arr_to_sort, arr_size);
////    print_arr(arr_to_sort, arr_size);
//    int* sorted;
//
//    clock_t start = clock();
//
//    sorted = quick_sort(arr_to_sort,0, arr_size - 1);
//
////    print_arr(sorted, arr_size);
//
//    clock_t end = clock();
//    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
//    printf("Sorting took %f seconds.\n", time_taken);
//
//    free(sorted);
    // free(arr_to_sort); already freed abow sorted* == arr_to_sort
//}