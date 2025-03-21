#include "iostream"



struct Node{
    int value;
    Node* previous;
};

Node* top = nullptr;
int siz = 0;

void push(int num){

    Node* n = new Node;
    n->previous = top;
    n->value = num;
    top = n;
    siz ++;
    printf("ok\n");
}

void back(){
    if (siz == 0){
        printf("error\n");
        return;
    }

    printf("%d\n", top->value);
}

void size(){
    printf("%d\n", siz);
}

void pop(){
    if (siz == 0){
        printf("error\n");
        return;
    }
    printf("%d\n", top->value);
    Node* buff = top;
    top = top->previous;
    delete buff;
    siz--;
}

void clear(){
//    Node* curr = top;
    while(top != nullptr){
        Node* buff = top;
        top = top->previous;
        delete buff;
    }

//    top = nullptr;
    siz = 0;
    printf("ok\n");
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

        if (curr == "back"){
            back();
        }

        if (curr == "size"){
            size();
        }

        if (curr == "pop"){
            pop();
        }

        if (curr == "clear"){
            clear();
        }

        std::cin >> curr;

    }

    printf("bye\n");
}
