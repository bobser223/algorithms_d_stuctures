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

Node* NIL = new Node{};

class Tree{
private:
    Node* root;

    static void initNode(Node* node, int key, int value){
        node->key = key;
        node->value = value;

        node->right = NIL;
        node->left = NIL;
        node->parent = NIL;

        node -> color = RED;
    }

    static bool exists(Node* n){
        return n != NIL;
    }

    void leftRotate(Node* node){}

    void rightRotate(Node* node){}

    void balance(Node* new_node){
        Node* uncle;
        while(new_node->parent->color != RED){
            if(new_node->parent == new_node->parent->parent->left){
                uncle = new_node->parent->parent->right;
                if (uncle->color == RED){
                    new_node ->parent->color = BLACK;
                    uncle->color = BLACK;
                    new_node->parent->parent->color = RED;
                    new_node = new_node->parent->parent;
                } else {
                    if(new_node == new_node->parent->right){
                        new_node = new_node->parent;
                        leftRotate(new_node); // todo complete
                    }
                    new_node -> parent->color = BLACK;
                    new_node -> parent -> parent -> color = RED;
                    rightRotate(new_node->parent->parent); // todo complete
                }
            }
            else {
                uncle = new_node->parent->parent->left;
                if (uncle->color == RED){
                    new_node->parent->color = BLACK;
                    uncle->color = BLACK;
                    new_node -> parent ->parent->color = RED;
                    new_node = new_node->parent->parent;
                }
                else {
                    if (new_node == new_node->parent->left){
                        new_node = new_node->parent;
                        rightRotate(new_node);
                    }
                    new_node -> parent ->color = BLACK;
                    new_node ->parent->parent->color = RED;
                    leftRotate(new_node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    static int childrenCount(Node* node){
        int count = 0;
        if (exists(node->left)) count++;
        if (exists(node ->right)) count++;
        return count;
    }

    Node* search(int value){
        Node* curr = root;
        while(curr != NIL){
            if (curr->value == value){
                return curr;
            }

            if (value < curr->value) curr = curr->left;
            else curr = curr ->right;
        }
        return NIL;
    }

    static Node* childOrMock(Node* node){
        return (exists(node->left) ? node->left:node->right);
    }

    void transplantNode(Node* to_node, Node* from_node){
        if (to_node == root)
            root = from_node;
        else if (to_node == to_node->parent->left)
            to_node->parent->left = from_node;
        else
            to_node->parent->right = from_node;
        from_node->parent = to_node->parent;
    }

    void  fixBalanceAfterDeleting(Node* node){
        while(node!= root && node->color == BLACK){
            Node* brother;
            if (node == node->parent->left){
                brother = node->parent->right;
                if (brother->color == RED){
                    brother->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    brother = node->parent->right;
                }
                if (brother->left->color == BLACK && brother->right->color == BLACK){
                    brother->color = RED;
                    node = node->parent;
                }
                else{
                    if (brother ->right->color == BLACK){
                        brother->left->color = BLACK;
                        brother->color = RED;
                        rightRotate(brother);
                        brother = node->parent->right;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->right->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            } else {
                brother = node->parent->left;
                if (brother->color == RED){
                    brother->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    brother = node->parent->left;
                }
                if (brother->left->color == BLACK && brother->right->color == BLACK){
                    rightRotate(node->parent);
                    brother = node->parent->left;
                } else {
                    if (brother->left->color == BLACK){
                        brother->right->color = BLACK;
                        brother->color = RED;
                        leftRotate(brother);
                        brother = node->parent->left;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->left->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }


public:
    Tree(){
        root = nullptr;
    }

    void insert(int key, int value){

        Node* curr_node = root;
        Node* parent = NIL;

        while(exists(curr_node)){
            parent = curr_node;
            if (value < curr_node->value) curr_node = curr_node -> left;
            else curr_node = curr_node -> right;
        }

        Node* new_node = new Node;
        initNode(new_node, key, value);
        new_node->parent = parent;

        if (parent == NIL)
            this->root = new_node;
        else if(value < parent->value)
            parent->left = new_node;
        else
            parent->right = new_node;

        balance(new_node);
    }





    void pop(int key){
        Node* node_to_delete = search(key);
        if (!exists(node_to_delete)) return;

        bool removed_node_color = node_to_delete->color;
        Node* child;
        if (childrenCount(node_to_delete) < 2){
            child = childOrMock(node_to_delete);
            transplantNode(node_to_delete, child);
        } else {
            Node* min_node = Min(node_to_delete->right);
            node_to_delete->key = min_node->key;
            node_to_delete->value = min_node->value;
            removed_node_color = min_node->color;
            child = childOrMock(min_node);
            transplantNode(min_node, child);
        }
        if (removed_node_color == BLACK) fixBalanceAfterDeleting(child);
    };







};