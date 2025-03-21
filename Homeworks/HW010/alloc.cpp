//
// Created by Volodymyr Avvakumov on 06.03.2025.
//
#include "iostream"





int main(){

    int* m = (int*)malloc(99999999999*sizeof(int));

    std::cout << m;

    free(m);
}