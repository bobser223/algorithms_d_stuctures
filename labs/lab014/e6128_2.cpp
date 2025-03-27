#include <iostream>
#include <string>

#define SIZE 100

int arr[SIZE];
int front = 0, back = 0, curr_size = 0;

void push_back(int v) {
    if (curr_size == SIZE) { std::cout << "error\n"; return; }
    arr[back] = v;
    back = (back + 1) % SIZE;
    curr_size++;
    std::cout << "ok\n";
}

void push_front(int v) {
    if (curr_size == SIZE) { std::cout << "error\n"; return; }
    front = (front - 1 + SIZE) % SIZE;
    arr[front] = v;
    curr_size++;
    std::cout << "ok\n";
}

void pop_front() {
    if (curr_size == 0) { std::cout << "error\n"; return; }
    std::cout << arr[front] << "\n";
    front = (front + 1) % SIZE;
    curr_size--;
}

void pop_back() {
    if (curr_size == 0) { std::cout << "error\n"; return; }
    back = (back - 1 + SIZE) % SIZE;
    std::cout << arr[back] << "\n";
    curr_size--;
}

void front_func() {
    if (curr_size == 0) std::cout << "error\n";
    else std::cout << arr[front] << "\n";
}

void back_func() {
    if (curr_size == 0) std::cout << "error\n";
    else std::cout << arr[(back - 1 + SIZE) % SIZE] << "\n";
}

void clear_deque() {
    front = back = curr_size = 0;
    std::cout << "ok\n";
}

void size_func() {
    std::cout << curr_size << "\n";
}

int main() {
    std::string cmd;
    while (std::cin >> cmd && cmd != "exit") {
        if (cmd == "push_back") { int x; std::cin >> x; push_back(x); }
        else if (cmd == "push_front") { int x; std::cin >> x; push_front(x); }
        else if (cmd == "pop_front") pop_front();
        else if (cmd == "pop_back") pop_back();
        else if (cmd == "front") front_func();
        else if (cmd == "back") back_func();
        else if (cmd == "size") size_func();
        else if (cmd == "clear") clear_deque();
    }
    std::cout << "bye\n";
    return 0;
}
