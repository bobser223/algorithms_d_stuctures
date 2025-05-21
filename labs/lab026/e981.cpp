#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


// Ваша структура
struct Node {
    int edge;
    int weights;

    friend std::istream& operator>>(std::istream& is, Node& n);
};

std::istream& operator>>(std::istream& is, Node& n) {
    is >> n.edge >> n.weights;
    return is;
}


struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.weights > b.weights;
    }
};

std::vector<std::vector<Node>> graph;


int prim_algo(int n){
    int count;
    std::vector<bool> used(n+1, false);
    std::priority_queue<Node, std::vector<Node>, CompareNode> minHeap;

    int total_weight = 0;
    int count_used = 0;

    used[1] = true;
    count_used = 1;

    // Кладемо в купу всі ребра з вершини 1
    for (auto& nei : graph[1]) {
        minHeap.push(nei);
    }

    while(!minHeap.empty() && count_used < n){
        auto [v_min,w_min ] = minHeap.top(); minHeap.pop();

        if (used[v_min]) continue;

        // Вибираємо це ребро до MST
        used[v_min] = true;
        total_weight += w_min;
        count_used++;


        for (auto& nei : graph[v_min]) {
            if (!used[nei.edge]) {
                minHeap.push(nei);
            }
        }
    }

    return  total_weight;

}

int main() {
    std::priority_queue<Node, std::vector<Node>, CompareNode> minHeap;
    int n, m;
    cin >> n >> m;
    graph.resize(n+1);
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    cout << prim_algo(n) << endl;

}