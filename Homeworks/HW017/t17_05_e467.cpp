#include <iostream>
#include <fstream>

struct Node{
    int value;

    Node* right;
    Node* left;

    explicit Node(int v): value(v), right(nullptr), left(nullptr){};

    ~Node(){
        delete right;
        delete left;
    }
};


class Tree{
private:
    Node* root;
public:
    Tree() = default;

    ~Tree(){
        delete root;
    }

    bool add(int value){
        Node* new_node = new Node(value);
        if (!root){
            root = new_node;
            return true;
        }

        Node* curr = root;
        Node* parent = nullptr;

        while (curr){

            if (new_node->value < curr->value){
                if (curr->right){
                    delete new_node;
                    return false;
                }

                parent = curr;
                curr = curr->left;

            } else if (new_node->value > curr->value){
                if (curr->left){
                    delete new_node;
                    return false;
                }
                parent = curr;
                curr = curr->right;

            } else {
                delete new_node;
                return true;
            }
        }

        if (new_node->value < parent->value){
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }


        return true;
    }
};



int main(){
    std::ifstream fin("input.txt");
    Tree t;

    int x;
    while(fin >> x){
        if (!t.add(x)){
            std::cout << "NO\n";
            return 0;
        }
    }

    std::cout << "YES\n";

}