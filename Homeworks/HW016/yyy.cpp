#include <vector>
#include <iostream>

using namespace std;

struct Node{
    int money;
    vector<Node*> kids;
};

class Tree{
    Node* root;
public:
    Tree(Node* node): root(node){};
};




int main(){
    int n;
    cin >> n;
    vector<Node*> pidors(n);

    for(int i = 0; i < n; i++){
        pidors[i] = new Node;
    }

    for (int i = 0; i < n; i++){ // through all pidors, i = pidor number - 1
        int money, kids_count, kid_number;
        vector<int> kids;
        cin >> money;
        cin >> kids_count;
        while (kids_count--){
            cin >> kid_number;

            pidors[i]->kids.push_back(pidors[kid_number]); // звязуємо дітей
        }
    }

    Tree t(pidors[0]);
}