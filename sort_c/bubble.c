//
// Created by Volodymyr Avvakumov on 16.02.2025.
//




int* bubble_sort(int* arr_to_sort, int size){
    for (int i = size - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if (arr_to_sort[j] > arr_to_sort[j + 1]){
                int buffer = arr_to_sort[j];
                arr_to_sort[j] = arr_to_sort[j+1];
                arr_to_sort[j+ 1] = buffer;
            }
        }
    }
    return arr_to_sort;
}