#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;
using sz = size_t;





struct edge {
    size_t vertex;
    size_t id;
    edge(int v, size_t i): vertex(v), id(i) {}
    ~edge() = default;
    bool operator==(edge const& o) const {
        return vertex == o.vertex && id == o.id;
    }
};

namespace std {
    template<>
    struct hash<edge> {
        size_t operator()(edge const& e) const noexcept {
            return (e.vertex * 31) ^ e.id;
        }
    };
}


void dfs(vector<unordered_set<edge>>& graph, set<int>& baned, int n){

    vector<bool> used(n+1, false);
    used[0] = true;

    stack<int> st;
    st.push(1);
    used[1] = true;

    while (!st.empty()){
        int curr = st.top(); st.pop();

        for (auto neighbor: graph[curr]){
            if (baned.contains(neighbor.id))
                continue;
            if (!used[neighbor.vertex]){
                st.push(neighbor.vertex);
                used[neighbor.vertex] = true;
            }

        }
    }

    for (bool var: used){
        if (!var){
            cout << "Disconnected" << endl;
            return;
        }
    }

    cout << "Connected" << endl;
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<unordered_set<edge>> graph(n+1);

    int b1, b2;
    for(sz i = 1; i <= m; i++){
        cin >> b1 >> b2;
        graph[b1].insert(edge{ b2, i });
        graph[b2].insert(edge{ b1, i });
    }

    int k, c;
    cin >> k;
    for(int i = 0; i < k; i++){
        cin >> c;
        set<int> baned;
        for (int j = 0; j < c; j++){
            cin >> b1;
            baned.insert(b1);
        }
        dfs(graph, baned, n);
    }




}