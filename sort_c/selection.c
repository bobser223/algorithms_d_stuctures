//
// Created by Volodymyr Avvakumov on 16.02.2025.
//


int* selection_sort(int* arr_to_sort, int size){
    for (int i = size - 1; i > 0; i--){
        int maxpos = 0;
        for(int j = 0; j < i+1; j++){
            if(arr_to_sort[maxpos] < arr_to_sort[j])
                maxpos = j;

        }
        int buffer = arr_to_sort[i];
        arr_to_sort[i] = arr_to_sort[maxpos];
        arr_to_sort[maxpos] = buffer;
    }
    return arr_to_sort;
}