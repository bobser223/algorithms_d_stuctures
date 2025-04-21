#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> vec;

void swap(int i1, int i2){
    int tmp = vec[i1];
    vec[i1] = vec[i2];
    vec[i2] = tmp;
}

void swift_down(int start, int end){
    while (true) {
        int left = start * 2 + 1;
        int right = left + 1;
        int largest = start;
        if (left < end and vec[left] > vec[largest])
            largest = left;
        if (right < end and vec[right] > vec[largest])
            largest = right;
        if (largest == start)
            break;
    }
}

void heap_sort(){
    int size = vec.size() - 1;

    for (int i = size / 2 -1; i > -1; i--){
        swift_down(i, size);
    }

    for (int i = size - 1; i > 0; i--){
        swap(i, 0);

    }
}


int main(){
    int buff;
    std::fstream fin("input.txt");
    while(fin >> buff){
        vec.push_back(buff);
    }
    heap_sort();
    for(auto var: vec)
        std::cout << var << " ";

}

