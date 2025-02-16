//
// Created by Volodymyr Avvakumov on 16.02.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef ALG_D_SRUCT_MERGE_H
#define ALG_D_SRUCT_MERGE_H

static int* copy_arr(int* arr, size_t begin, size_t end);

static int* merge(int* arr_a, int* arr_b,size_t a_size, size_t b_size);

int* merge_sort(int *arr_to_sort, size_t arr_size);


#endif //ALG_D_SRUCT_MERGE_H
