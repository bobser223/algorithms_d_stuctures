#include <clocale>
#include <iostream>
#include <fstream>


class Node
{
public:
    int data;
    Node *next;
    Node() : next(NULL) {};
    Node(int data, Node *next = NULL) : data(data), next(next) {};
};

class List
{
public:
    Node *head, *tail;
    size_t size;
    List() : head(NULL), tail(NULL), size(0) {};

    ~List(){
        Node* curr = head;
        Node* tmp;
        while(curr){
            tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }

    void addToTail(int val) // Додати число val в кінець Зв’язного Списку
    {
        Node* node = new Node{val, NULL};

        size++;

        if (head == NULL){
            head = tail = node;
            return;
        }

        tail->next = node;
        tail = node;
    }
    void Print(void) // Вивести елементи Зв’язного Списку
    {
        Node* tmp = head;
        while(tmp != NULL){
            std::cout << tmp->data << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }
    void RotateRight(int k) // Здійснити обертання Зв’язного Списку праворуч на k позицій
    {
        k %= size;

        for (size_t i = 0; i < k; i++){
            push_front_tail();
        }

    }


    void push_front_tail(){
//        if (!tail || !head) return;

        Node* tmp = new Node{tail->data, head}; // copy tail and poit to head
        head = tmp;
        delete tail ;

        Node* curr = head->next;
        while (curr ->next && curr->next != tail){
            curr = curr->next;
        }
        tail = curr;
        tail->next = nullptr;
    }
};


int main(){
    std::ifstream fin("input.txt");

    List lst;
    int n, buff;

    fin >> n;
    while(n){
        fin >> buff;
        lst.addToTail(buff);
        n--;
    }

    while(fin >> n){
        lst.RotateRight(n);
        lst.Print();
    }

    fin.close();

    return 0;
}