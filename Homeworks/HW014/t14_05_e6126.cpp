#include <string>
#include <iostream>

using std::cout, std::endl;

struct Node {
    int value;
    Node* next;

//    Node(int n, Node* ptr){
//        value = n;
//        next = ptr;
//    }
};

Node* top = nullptr;
Node* bottom = nullptr;
int SIZE = 0;
// top -> . . . . . . -> bottom

void push(int n){
    Node* tmp = new Node{n, nullptr};
    SIZE++;

    if (!top || !bottom){
        top = tmp;
        bottom = tmp;
        cout << "ok" << endl;
        return;
    }

    bottom->next = tmp;
    bottom = tmp;

    cout << "ok" << endl;
}

void size(){
    std::cout << SIZE << std::endl;
}

void pop() {

    if (SIZE == 0 || !top) {
        cout << "error" << endl;
        return;
    }
    SIZE--;

    cout << top->value << endl;

    Node *tmp = top;
    top = top->next;
    delete tmp;
}

void front_func(){
    if (SIZE == 0 || !top) {
        cout << "error" << endl;
        return;
    }

    cout << top->value << endl;
}

void clear(){
    SIZE = 0;

    while (top){
        Node *tmp = top;
        top = top->next;
        delete tmp;
    }

    cout << "ok" << endl;
}



int main(){
    std::string curr;
    std::cin >> curr;
    while(curr != "exit"){
        if (curr == "push"){
            int num;
            std::cin >> num;
            push(num);
        }


        if (curr == "size"){
            size();
        }

        if (curr == "pop"){
            pop();
        }

        if (curr == "front"){
            front_func();
        }

        if (curr == "clear"){
            clear();
        }

        std::cin >> curr;

    }
    printf("bye\n");
}