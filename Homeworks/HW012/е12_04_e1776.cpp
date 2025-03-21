#include <iostream>
#include <vector>

struct Node{
    int value;
    Node* previous;

};

class stack{
private:
    Node* top = nullptr;
    int counter = 0;
public:
    stack()= default;
    ~stack(){
        while (top != nullptr){
            Node* buff = top;
            top = top ->previous;
            counter--;
            delete buff;
        }
    }


    void push(int value){
        counter++;
        Node* new_node = new Node;
        new_node->previous = top;
        new_node->value = value;
        top = new_node;
    }

    int pop(){
        counter--;
        int result = top ->value;
        Node* buff = top;
        top = top -> previous;
        delete buff;
        return result;
    }

    [[nodiscard]] int show() const{
        return top->value;
    }

    [[nodiscard]] bool empty() const{
        return counter == 0;
    }
};


bool can_return(std::vector<int>& vec){

    stack station;
    int curr = 1;

    int size = vec.size();

    for (int i = 0; i < size; i++){
        int target = vec[i];

        while(curr <= size && (station.empty() || station.show() != target)){
            station.push(curr);
            curr++;
        }

        if (!station.empty() && station.show() == target){
            station.pop();
        } else {
            return false;
        }

    }
    return true;
}



int main() {
    while (true) {

        int count;
        std::cin >> count;

        if (!count) break;

        while (true){
            std::vector<int> permutations(count);
            std::cin >> permutations[0];
            if (!permutations[0]){
                printf("\n");
                break;
            }

            for (int i = 1; i < count; i++){
                std::cin >> permutations[i];
            }
            std::cout << (can_return(permutations) ? "Yes\n" : "No\n");

        }
    }
}