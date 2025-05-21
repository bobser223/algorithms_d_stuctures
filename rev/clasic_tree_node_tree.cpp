

#include <iostream>
#include <vector>
#include <queue>


class Tree{
    int value;
    std::vector<Tree*> kids;

    explicit Tree(int val): value(val){}

    ~Tree(){
        for (auto kid: kids)
            delete kid;
    }

    void set_key(int val){
        value = val;
    }

    int key() const{
        return value;
    }

    void add_kid(Tree& t){
        kids.push_back(&t);
    }

    void remove_child(int key){
        for (auto kid: kids){
            if (kid ->value == key){
                delete kid;
            }
        }
    }

    std::vector<Tree*> get_children(){
        return kids;
    }

    Tree* get_child(int key){
        for (auto kid: kids){
            if (kid->value == key)
                return kid;
        }
        return nullptr;
    }

    void do_something(){}

    void BFS(Tree* t){
        std::queue<Tree*> q;
        q.push(t);

        while(!q.empty()){
            Tree* curr = q.front(); q.pop();
            do_something();
            for (auto kid: curr->kids){
                q.push(kid);
            }
        }
    }





};
