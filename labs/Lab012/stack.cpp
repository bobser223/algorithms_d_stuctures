
#include <iostream>

int arr[100];

int curr_index = 0;

void push(int num){
    arr[curr_index++] = num;
    printf("ok\n");
}

void pop(){
    std::cout << arr[--curr_index ] << std::endl;

}

void back(){
    std::cout << arr[curr_index - 1] << std::endl;
}

void size(){
    std::cout << curr_index << std::endl;
}

void clear(){
    curr_index = 0;
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