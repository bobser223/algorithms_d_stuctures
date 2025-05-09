#include <clocale>
#include <iostream>


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
    List() : head(NULL), tail(NULL) {};
    void addToTail(int val) // Додати число val в кінець Зв’язного Списку
    {
        Node* node = new Node{val, NULL};

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
    void PrintReverse(void) // Вивести елементи Зв’язного Списку в зворотному порядку
    {
        reverse();
        Print();

    }
    void reverse(){
        Node* prev = nullptr;
        Node* curr = head;
        tail = head;
        while (curr != nullptr){
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev;
    }
};


int main(){
    List list;
    int n, buff;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        std::cin >> buff;
        list.addToTail(buff);
    }
    list.Print();
    list.PrintReverse();
}