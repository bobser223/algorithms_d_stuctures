#include <iostream>
#include <vector>

struct Node{
    int value;
    std::vector<Node*> kids;

    ~Node(){
        for (auto kid: kids){
            delete kid;
        }
    }

};



class Tree{
    Node* root;

    Tree(): root(nullptr){}
    ~Tree(){
        delete root;
    }

    void add_kid(int val){
        auto tmp = new Node(val);
        root->kids.push_back(tmp);
    }
};