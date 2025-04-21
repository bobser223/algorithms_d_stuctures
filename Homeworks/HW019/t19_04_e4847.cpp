#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

struct bucket{
    std::string value;
    int priority;

    bucket(std::string str, int pr): value(std::move(str)), priority(pr){}
    ~bucket() = default;

    bool operator < (const bucket& other) const {
        return this->priority < other .priority;
    }

    bool operator == ( const bucket& other) const{
        return this->priority == other .priority;
    }

    bool operator > (const bucket& other) const {
        return this->priority > other .priority;
    }
};


std::vector<bucket> HEAP;
int SIZE = 0;

void sift_up(int index = HEAP.size() -1 ){
    while (index > 1){ // ось тут по факту ми доходимо до реального першого елементу(кореня), в нас 0-вий буферий
        int parent_index = index/2;
        if (HEAP[index] < HEAP[parent_index])
            std::swap(HEAP[index], HEAP[parent_index]);
        else
            break;
        index = parent_index;
    }
}

void sift_down(int index = 1){
    while(2*index <= SIZE){
        int left = 2*index;
        int right = 2*index + 1;
        int min_kid_index;

        if (HEAP[left] < HEAP[right])
            min_kid_index = left;
        else
            min_kid_index = right;

        if (HEAP[index] < HEAP[min_kid_index])
            std::swap(HEAP[index], HEAP[min_kid_index]);
        else
            break;
        index = min_kid_index;
    }
}



void change(const std::string& id, int new_priority){

    int index_for_change = 0;
    for (int i = 1; i < SIZE+1; i++){
        if (HEAP[i].value == id){
            index_for_change = i;
            break;
        }
    }

    int old_priority = HEAP[index_for_change].priority;

    HEAP[index_for_change].priority = new_priority;

    if (old_priority < new_priority)
        sift_down(index_for_change);
    else if (old_priority > new_priority)
        sift_up(index_for_change);

}

void insert(const std::string& str, int priority){
    SIZE++;
    HEAP.emplace_back(str, priority); // HEAP.push_back({str, priority});
    sift_up();
}

void pop(){
    SIZE--;
    std::cout << HEAP[1].value << " " <<  HEAP[1].priority << std::endl;
    HEAP[1] = HEAP.back();
    HEAP.pop_back();
    sift_down();

}

int main(){
    HEAP.emplace_back("ZERO", -100500); // HEAP.push_back({"ZERO", -100500});
    std::fstream fin("input.txt");
    int priority;
    std::string id, buff;

    while(fin >> buff){
        if (buff == "ADD"){
            fin >> id;
            fin >> priority;
            insert(id, priority);
        } else if (buff == "POP"){
            pop();
        } else if (buff == "CHANGE"){
            fin >> id;
            fin >> priority;
            change(id, priority);
        }
    }
}




