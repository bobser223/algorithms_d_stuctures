//
// Created by Volodymyr Avvakumov on 08.05.2025.
//
#include <iostream>


struct Node{
    int value;
    Node* next;
};

Node* top = nullptr;

void add(int a){

    Node* tmp = new Node{a, top};

    top = tmp;

}


void del(){
    Node* tmp = top;
    top = top->next;
    delete tmp;
}

int _top(){
    return top->value;
}

int main(){
    int n;
    std::cin >> n;




}