#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

struct Node{
    int color;
    int number;
    std::vector<Node*> kids;
    explicit Node(int color) : color(color) {};
    Node() = default;
    ~Node() = default;
};


class Tree{
private:
    Node* root;
public:
    explicit Tree(Node* rt){
        root = rt;
    }

    ~Tree() = default;


    Node* DFS(int number){
        if (!root){
            return nullptr;
        }
        std::stack<Node*> st;

        st.push(root);

        while(!st.empty()){

            Node* curr = st.top(); st.pop();

            if (curr->number == number) return curr;

            for (auto kid: curr->kids)
                st.push(kid);

        }
        return nullptr;
    }

    static int count_DFS(Node* node){
        std::stack<Node*> st;
        std::unordered_set<int> colors;

        st.push(node);

        while(!st.empty()){
            Node* curr = st.top(); st.pop();
            colors.insert(curr->color);
            for(auto kid: curr->kids)
                st.push(kid);
        }

        return colors.size();
    }

    void colors_count(int count){
        for (int i = 1; i < count+1; i++){
            Node* curr = DFS(i);
            std::cout << count_DFS(curr) << " ";
        }

    }
};


struct Node_status{
    int parent;
    int color;
};

int main(){
    int n;
    std::cin >> n;

    std::vector<Node*> node_vec(n+1);

    for (int i = 0; i < n+1; i++) node_vec[i] = new Node;

    std::unordered_map<int, Node_status> map;

    for(int i = 1; i < n+1; i++){
        int parent, color;
        std::cin >> parent >> color;
        map[i] = {parent, color};
    }

    node_vec[0] ->number = 0;
    for (int i = 1; i < n+1; i++){
        node_vec[i]->number = i;
        node_vec[i] ->color = map[i].color;
        node_vec[map[i].parent] ->kids.push_back(node_vec[i]);
    }

    Tree tree(node_vec[0]);

    tree.colors_count(n);



}