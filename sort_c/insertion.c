//
// Created by Volodymyr Avvakumov on 16.02.2025.
//



int* insertion_sort(int* arr_to_sort, int size){

    for (int i = 0; i < size; i++){
        int curr = arr_to_sort[i];
        int position = i;
        while(position > 0){
            if (arr_to_sort[position - 1] > curr)
                arr_to_sort[position] = arr_to_sort[position -1];
            else
                break;
            position--;
        }
        arr_to_sort[position] = curr;
    }
    return arr_to_sort;

}