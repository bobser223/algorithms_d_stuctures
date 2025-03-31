#include <string>
#include <iostream>

using std::cout, std::endl;

struct Node {
    int value;
    Node* next;
    Node* previous;

};

Node* top = nullptr;
Node* bottom = nullptr;
int SIZE = 0;
// top -> . . . . . . -> bottom
//     <-             <-


void push_back(int value){

    SIZE++;

    if (!top || !bottom){
        Node* curr = new Node{value, nullptr, nullptr};
        top = curr;
        bottom = curr;
        cout << "ok" << endl;
        return;
    }

    Node* curr = new Node{value, nullptr, bottom};
    bottom->next = curr;
    bottom = curr;
    cout << "ok" << endl;

}

void push_front(int value){
    SIZE++;

    if (!top || !bottom){
        Node* curr = new Node{value, nullptr, nullptr};
        top = curr;
        bottom = curr;
        cout << "ok" << endl;
        return;
    }

    Node* curr = new Node{value, top, nullptr};
    top->previous = curr;
    top = curr;
    cout << "ok" << endl;
}

void size(){
    cout << SIZE << endl;
}

void pop_front(){
    if (!top || SIZE == 0){
        cout << "error" << endl;
        return;
    }


    SIZE--;

    cout << top->value << endl;

//    top = top->next;
//    delete top->previous;
//    top -> previous = nullptr;
    Node* tmp = top;
    top = top->next;
    delete tmp;
    if (top)
       top ->previous = nullptr;
    else
        bottom = nullptr;
}

void pop_back(){
    if (!bottom || SIZE == 0){
        cout << "error" << endl;
        return;
    }

    SIZE--;

    cout << bottom->value << endl;

//    bottom = bottom -> previous;
//    delete bottom -> next;
//    bottom -> next = nullptr;
    Node* tmp = bottom;
    bottom = bottom ->previous;
    delete tmp;
    if (bottom)
        bottom->next = nullptr;
    else
        top = nullptr;
}

void front_func(){
    if (!top || SIZE == 0){
        cout << "error" << endl;
        return;
    }
    cout << top->value << endl;
}

void back_func(){
    if (!bottom || SIZE == 0){
        cout << "error" << endl;
        return;
    }
    cout << bottom->value << endl;
}

void clear(){
    if (!top || !bottom || SIZE == 0) {
        cout << "ok" << endl;
        return;
    }
    SIZE = 0;

    while(top){
        Node* tmp = top;
        top = top->next;
        delete tmp;
    }
    bottom = nullptr;
    cout << "ok" << endl;
}

int main(){
    std::string curr;
    std::cin >> curr;
    while(curr != "exit"){
        if (curr == "push_back"){
            int num;
            std::cin >> num;
            push_back(num);
        }

        if (curr == "push_front"){
            int num;
            std::cin >> num;
            push_front(num);
        }


        if (curr == "size"){
            size();
        }

        if (curr == "pop_front"){
            pop_front();
        }

        if (curr == "pop_back"){
            pop_back();
        }

        if (curr == "front"){
            front_func();
        }

        if (curr == "clear"){
            clear();
        }

        if (curr == "back"){
            back_func();
        }

        std::cin >> curr;

    }
    printf("bye\n");
}
