//
// Created by Volodymyr Avvakumov on 16.02.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#ifndef ALG_D_SRUCT_QUICK_H
#define ALG_D_SRUCT_QUICK_H

void print_arr(int* arr, size_t size);

static void fill_arr(int* arr, size_t size);

static void swap(int* arr, int first_position, int second_position);

int* quick_sort(int* arr_to_sort, int begin, int end);


#endif //ALG_D_SRUCT_QUICK_H
