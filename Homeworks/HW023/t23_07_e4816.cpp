#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <print>

using namespace std;

void DFS(int id, const vector<vector<int>>& graph, vector<int>& cc, vector<bool>& used){
    std::stack<int> st;
    used[id] = true;
    cc.push_back(id);
    st.push(id);
    while(!st.empty()){

        int curr = st.top(); st.pop();

        for (int vertex: graph[curr]){
            if (!used[vertex]){
                st.push(vertex);
                used[vertex] = true;
                cc.push_back(vertex);
            }
        }
    }
}

void findConnectivityComponents(const vector<vector<int>>& graph){
    std::vector<bool> used(graph.size()+1, false);
    used[0] = true;

    vector<vector<int>> connectivity_components;

    for (int i = 1; i < graph.size(); i++){
        if (used[i]) continue;
        vector<int> cc;
        DFS(i, graph, cc, used);
        connectivity_components.push_back(cc);
    }

    println("{}", connectivity_components.size());

    for(const auto& cc: connectivity_components){
        println("{}", cc.size());
        for (int v: cc){
            print("{} ", v);
        }
        println();
    }


}


int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);

    int b1, b2;
    for (int i = 0; i < m; i++){
        cin >> b1 >> b2;
        graph[b1].push_back(b2);
        graph[b2].push_back(b1);
    }

    findConnectivityComponents(graph);

}
