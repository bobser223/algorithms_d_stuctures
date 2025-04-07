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

class List {
public:
    Node *head, *tail;

    size_t size;

    List() : head(NULL), tail(NULL), size(0) {};

    void addToTail(int val) // Додати число val в кінець Зв’язного Списку
    {
        size++;
        Node *node = new Node{val, NULL};

        if (head == NULL) {
            head = tail = node;
            return;
        }

        tail->next = node;
        tail = node;
    }

    void Print(void) // Вивести елементи Зв’язного Списку
    {
        Node *tmp = head;
        while (tmp) {
            std::cout << tmp->data << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }

    void ReorderList(void) // Перегрупувати елементи списку як наведено вище
    {
        size_t iter = size / 2;
//
//        std::cout << iter;

        int k = 1;
        for(size_t i = 0; i < iter; i++){
            tail_to_k_position(k);
            k+=2;
        }
    }

    void tail_to_k_position(int k){

        Node* tmp = new Node{tail->data, nullptr};

        ////////////// deleting tail
        Node* curr = head;
        while(curr->next != tail && curr->next){
            curr = curr->next;
        }
        delete curr->next;
        tail = curr;
        tail->next = NULL;
        ///////////////

        curr = head;
        for (int i = 0; i < k-1; i++){
            curr = curr->next;
        }

        tmp->next = curr->next;
        curr->next = tmp;

    }
};



int main(){
    List lst;
    int n, buff;
    std::cin >> n;

    while(n--){
        std::cin >> buff;
        lst.addToTail(buff);
    }

    lst.ReorderList();
    lst.Print();
}