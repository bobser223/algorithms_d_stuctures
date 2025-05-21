//
// Created by Volodymyr Avvakumov on 07.04.2025.
//
#include <iostream>
#include <stack>
#include <limits>


struct Node{
    int value;
    Node* right;
    Node* left;
};



class Tree{
private:
    Node* root;

public:
    Tree(){
        root = nullptr;
    }

    void insert(int n) {
        Node* new_node = new Node{n, nullptr, nullptr};

        if (!root) {
            root = new_node;
            return;
        }

        Node* curr = root;
        while (true) {
            if (n == curr->value) {
                // Вузол вже існує, тому звільняємо пам'ять нового вузла.
                delete new_node;
                return;
            }
            if (n < curr->value) {
                if (!curr->left) {
                    curr->left = new_node;
                    return;
                } else {
                    curr = curr->left;
                }
            } else {  // n > curr->value
                if (!curr->right) {
                    curr->right = new_node;
                    return;
                } else {
                    curr = curr->right;
                }
            }
        }
    }

    int find_max(){
        Node* curr = root;
        while(curr) {
            if (curr->right) {
                curr = curr->right;
            } else {
                return curr->value;
            }
        }
        return root->value;
    }

    void DFS() {
        if (!root) {
            return;
        }

//        if (!root->right){
//            return;
//        }

        int max_2 = std::numeric_limits<int>::min(), max = find_max();
        std::stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            auto current = s.top();
            s.pop();

            Node* node = current;

            if (node) {
                if (node->value > max_2 && node->value != max)
                    max_2 = node->value;


                if (node->right) {
                    s.push(node->right);
                }
                if (node->left) {
                    s.push(node->left);
                }
            }
        }
        std::cout << max_2 << std::endl;
    }
};

int main(){
    Tree  t;
    int n;
    std::cin >> n;
    while(n!= 0){
        t.insert(n);
        std::cin >> n;
        if (n == 0) break;
    }

    t.DFS();
}