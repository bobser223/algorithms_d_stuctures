#include <iostream>
#include <stack>
#include <string>




struct Node {
    std::string name;

    Node* right;
    Node* left;

    explicit Node(std::string str): name(std::move(str)), right(nullptr), left(nullptr) {}

    ~Node(){
        delete left;
        delete right;
    }
};


class Tree{
private:
    Node* root;
public:
    Tree(): root(nullptr) {}

    void add(const std::string& str){
        Node* new_node = new Node(str);
        if (!root){
            root = new_node;
            return;
        }

        auto curr = root;
        Node* parent = nullptr;

        while(curr){
            parent = curr;
            if (new_node->name < curr->name)
                curr = curr->left;
            else if (new_node->name > curr->name)
                curr = curr->right;
            else {
                delete new_node;
                return;
            }
        }

        if (new_node->name < parent->name){
            parent->left = new_node;
        } else {
            parent ->right = new_node;
        }



    }

    void print(){
        std::stack<Node*> st;
        st.push(root);
        while(!st.empty()){
            auto curr = st.top();
            st.pop();
            std::cout << curr->name;
            if(curr->right) st.push(curr->right);
            if(curr->left)  st.push(curr->left);
        }
    }

};


int main(){
    std::string buff;
    Tree t;
    std::stack<std::string> st;
    while(true){
        std::cin >> buff;
        if (buff == "*") break;
        st.push(buff);
    }

    while (!st.empty()){
        auto& str = st.top(); st.pop();
        for(auto& ch: str){
            t.add({ch});
        }
    }
    t.print();

}