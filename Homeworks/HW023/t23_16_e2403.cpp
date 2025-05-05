#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <print>

using namespace std;

void DFS(int id, const vector<vector<int>>& graph, vector<bool>& used, stack<int>& gl_st){

    used[id] = true;

        for (int vertex: graph[id]){
            if (!used[vertex]){

                used[vertex] = true;
                DFS(vertex, graph, used, gl_st);

            }
        }
        gl_st.push(id);

}

void DFS2(int id, const vector<vector<int>>& graphT, vector<bool>& used){
    std::stack<int> st;
    used[id] = true;
    st.push(id);
    while(!st.empty()){

        int curr = st.top(); st.pop();

        for (int vertex: graphT[curr]){
            if (!used[vertex]){
                st.push(vertex);
                used[vertex] = true;
            }
        }
    }
}

void Cosaradgu(const vector<vector<int>>& graph, const vector<vector<int>>& graphT){
    std::vector<bool> used(graph.size()+1, false);
    used[0] = true;
    stack<int> st;
    for (int i = 1; i < graph.size(); i++){
        if (!used[i])
            DFS(i, graph, used, st);
    }

    std::vector<bool> used2(graph.size()+1, false);
    used2[0] = true;
    int scc_count = 0;

    while (!st.empty()){
        int curr = st.top(); st.pop();
        if (!used2[curr]){
            DFS2(curr, graphT, used2);
            scc_count++;
        }
    }

    println("{}", scc_count);
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1), graphT(n+1);

    int b1, b2;
    for (int i = 0; i < m; i++){
        cin >> b1 >> b2;
        graph[b1].push_back(b2);
        graphT[b2].push_back(b1);
    }

    Cosaradgu(graph, graphT);

}

