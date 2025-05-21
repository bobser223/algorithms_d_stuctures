//
// Created by Volodymyr Avvakumov on 21.05.2025.
//



#include <cstdio>

#define sz size_t

template <typename T>
class vector{
private:
    T* arr;
    sz real_size;
    sz curr_size;

    void resize(){}

public:
    vector(sz reservation_size, T value_to_fill){
        real_size = curr_size = reservation_size;
        arr = new T[reservation_size];

        for(sz i = 0; i < reservation_size; i++){
            arr[i] = value_to_fill;
        }

    }

    explicit vector(int reservation_size){
        arr = new T[reservation_size];
        real_size = reservation_size;
        curr_size = 0;
    }

    const T& operator [](sz i){
        return arr[i];
    }

//    T operator[](sz i){
//        return arr[i];
//    }

    void push_back(T val){
        if (real_size == curr_size) resize();

        arr[curr_size++] = val;
    }

    void pop_back(){
        curr_size--;
    }

    T front(){
        if (!curr_size){
            return arr[0];
        }
    }





};