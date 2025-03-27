#include <iostream>

#define SIZE 100
//int SIZE = 100;

int arr[SIZE];

int front = 0;

int back = 0;

int curr_size = 0;


void push(int value){
    int pos = back;
    arr[pos] = value;
    back = (back + 1) % SIZE;
    printf("ok\n");

    curr_size++;
}

void front_func(){
    printf("%d\n", arr[front]);
}


void pop(){

    printf("%d\n", arr[front]);
    front = (front+1) % SIZE;
    curr_size--;
}

void clear(){
    front = 0;
    back = 0;
    curr_size = 0;
    printf("ok\n");
}

void size(){
    printf("%d\n", curr_size);
}

void push_front(int value){
    int pos = (front - 1 + SIZE) % SIZE;

    arr[pos] = value;
    curr_size ++;
    printf("ok\n");
}

void pop_back(){
    back = (back - 1 + SIZE) % SIZE;
    printf("%d\n", arr[back]);

}

void back_func(){
    back = (back - 1 + SIZE) % SIZE;
    printf("%d\n", arr[back]);
}

int main(){
    std::string curr;
    std::cin >> curr;
    while(curr != "exit"){
        if (curr == "push_back"){
            int num;
            std::cin >> num;
            push(num);
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
            pop();
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