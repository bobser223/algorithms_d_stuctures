#include <time.h>

#include "quick.h"
#include "merge.h"
#include "reader.h"
#include "selection.h"
#include "bubble.h"
#include "insertion.h"
#include "bottom_merge.h"

#include "nums_generator.h"


#define NUM_COUNT 1000000000


void legit_check(int* arr, int size, char* sort_name){
    for (int i = 0; i < size - 1; i++){
        if (arr[i] > arr[i+1])
            printf("taobao detected %s\n", sort_name);
    }
    printf("test passed by %s\n", sort_name);
}



int main(void){

    generate(NUM_COUNT);

    int* arr = (int*)calloc(NUM_COUNT, sizeof(int));
    int* sorted = (int*)calloc(NUM_COUNT, sizeof(int));
    clock_t start = clock();
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

// /////////////////////// merge /////////////////////

//    read(arr, NUM_COUNT);
//
//    start = clock();
//
//    sorted = merge_sort(arr, NUM_COUNT);
////    print_arr(sorted, NUM_COUNT);
//
//    end = clock();
//
//    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
//
//    printf("Sorting %d elements by merge sort took %f seconds.\n",NUM_COUNT, time_taken);
//    legit_check(sorted, NUM_COUNT, "merge");

/////////////////////////// b_merge ////////////////////////////
    read(arr, NUM_COUNT);

    start = clock();


    printf("sorting started\n");

    bottomUpMergeSort(arr, NUM_COUNT);

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorting %d elements by merge sort took %f seconds.\n",NUM_COUNT, time_taken);
    legit_check(arr, NUM_COUNT, "bottom merge");

//////////////////////////// quick /////////////////////
    read(arr, NUM_COUNT);

    start = clock();

    arr = quick_sort(arr, 0, NUM_COUNT - 1);

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorting %d elements by quick sort took %f seconds.\n",NUM_COUNT, time_taken);
    legit_check(arr, NUM_COUNT, "quick");
////////////////////////////// selection ///////////////////
    read(arr, NUM_COUNT);

    start = clock();

    arr = selection_sort(arr, NUM_COUNT);

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorting %d elements by selection sort took %f seconds.\n",NUM_COUNT, time_taken);
    legit_check(arr, NUM_COUNT, "selection");
////////////////////////////// insertion ///////////////////
    read(arr, NUM_COUNT);

    start = clock();

    arr = insertion_sort(arr, NUM_COUNT);

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorting %d elements by insertion sort took %f seconds.\n",NUM_COUNT, time_taken);
    legit_check(arr, NUM_COUNT, "insertion");
    ////////////////////////////// bubble ///////////////////
    read(arr, NUM_COUNT);

    start = clock();

    arr = bubble_sort(arr, NUM_COUNT);

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorting %d elements by bubble sort took %f seconds.\n",NUM_COUNT, time_taken);
    legit_check(arr, NUM_COUNT, "bubble");
//
    free(sorted);
    free(arr);


}