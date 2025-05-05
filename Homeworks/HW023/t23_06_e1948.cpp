#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
#include <set>


#define WHITE 0
#define BLACK 2
#define GRAY 1


using namespace std;
using sz = size_t;

struct Node{
    sz value;
    int color;
    unordered_set<Node> neighbours;


    explicit Node(int val):value(val) {
        color = WHITE;
    }


};

void topological_sort(vector<Node>& graph, sz n){


}


int main(){
    sz n, m;
    cin >> n >> m;

    vector<Node> graph;

    sz b1, b2;
    for(sz i = 0; i < m; i++){
        cin >> b1 >> b2;
        graph[b1].neighbours.insert(b2);
    }


}