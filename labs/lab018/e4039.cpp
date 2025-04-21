#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int SIZE = 0;
vector<int> heap;

void swap(int i1, int i2){
    int tmp = heap[i1];
    heap[i1] = heap[i2];
    heap[i2] = tmp;
}
void sift_down(){
    int i = 1;
    while(2*i <= SIZE){
        int left = 2*i;
        int right = 2*i + 1;
        int min;
        if (heap[left] < heap[right])
            min = left;
        else
            min = right;
        if (heap[i] > heap[min])
            swap(i, min);
        else
            break;
        i = min;
    }
}

void sift_up(){
    int i = heap.size() - 1;
    while(i > 0){
        int parent = i /2;
        if (heap[i] < heap[parent])
            swap(i, parent);
        else
            break;
        i = parent;
    }
}

void extract(){
    int root = heap[1];
    heap[1] = heap.back();
    SIZE--;
    heap.pop_back();
    sift_down();
    std::cout << root << std::endl;

}

void insert(int value){
    SIZE++;
    heap.push_back(value);
    sift_up();
}

int main(){
    heap.push_back(-1);
    int buff;
    std::fstream fin("input.txt");
    fin >> buff;
    while (fin >> buff){
        if (buff == 1){
            extract();
        } else {
            fin >> buff;
            insert(buff);
        }
    }
}