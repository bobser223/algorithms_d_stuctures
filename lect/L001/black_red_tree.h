//
// Created by Volodymyr Avvakumov on 15.03.2025.
//

#ifndef ALG_D_SRUCT_BLACK_RED_TREE_H
#define ALG_D_SRUCT_BLACK_RED_TREE_H

#define BLACK false
#define RED true





#endif //ALG_D_SRUCT_BLACK_RED_TREE_H

struct Node{
    int key;
    int value;

    Node* parent;
    Node* left;
    Node* right;

    bool color;

    Node(){
        color = BLACK;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    Node (int key, int value){
        this -> key = key;
        this -> value = value;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};


class Tree{
private:
    Node* root;

    static void init_node(Node* node, int key, int value){
        node->key = key;
        node->value = value;
        node->right = nullptr;
        node->left = nullptr;
        node->parent = nullptr;
    }

public:
    Tree(){
        root = nullptr;
    }

    void insert(int key, int value){
        if (!exists(root)){

            return;
        }

        Node* curr_node = root;
        Node* parent = nullptr;

        while(exists(curr_node)){
            parent = curr_node;
            if (value < curr_node->value) curr_node = curr_node -> left;
            else curr_node = curr_node -> right;
        }

        Node* new_node = new Node;
        init_node(new_node, key, value);


    }

    static bool exists(Node* n){
        return n != nullptr;
    }


};