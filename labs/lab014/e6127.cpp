#include <iostream>



struct Node{
    int value;
    Node* next;
};

Node* back = nullptr;
Node* front = nullptr;

int real_size = 0;

void push(int value){
    real_size++;
    if (back == nullptr){
        Node* new_back = new Node;
        new_back->value = value;
        new_back->next = nullptr;
        back = new_back;

        if (front == nullptr){
            front = back;
        }

        printf("ok\n");
        return;
    }

    Node* new_back = new Node;
    new_back->value = value;
    new_back->next = nullptr;
    back->next = new_back;
    back = new_back;


    printf("ok\n");


}


void pop(){
    if (!front) {
        std::cout << "error\n";
        return;
    }
    std::cout << front->value << "\n";

    Node* tmp = front;
    front = front->next;
    delete tmp;
    real_size--;
    if (!front) back = nullptr;

}


void clear(){
    while(front!= nullptr){
        Node* buff = front;
        front = front->next;
        delete buff;
    }
    back = nullptr;
    real_size = 0;
    printf("ok\n");

}

void size(){
    printf("%d\n", real_size);
}

void front_func(){
    if (!front) {
        std::cout << "error\n";
        return;
    }
    printf("%d\n", front->value);
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