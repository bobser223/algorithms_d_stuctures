#include <vector>
#include <iostream>
#include <stack>

#define INF 1005000

using namespace std;


struct edge{
    int priority;
    int to;
};

void show_way(const std::vector<int>& prev, int start, int end){
    std::stack<int> st;
    int curr = end;
    while(true){
        st.push(curr);
        curr = prev[curr];
        if (curr == start){
            st.push(curr);
            break;
        }
    }

    while(!st.empty()){
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}


void BelmanFord(vector<vector<edge>>& graph, int start, int end){
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<int> prev(n, -1);
    dist[start] = 0;

    for (int _ = 0; _ < n-1; _++){
        for (int vertex = 1; vertex < n; vertex++){
            for (auto [neighbours_priority, neighbour]: graph[vertex]){
                if (dist[neighbour] > dist[vertex] + neighbours_priority){
                    dist[neighbour] = dist[vertex] + neighbours_priority;

                    prev[neighbour] = vertex;
                }
            }
        }
    }
    if (dist[end] < INF) {
        cout << dist[end] << endl;
        show_way(prev, start, end);
    }else
        cout << -1 << endl;
}


int main(){
    int n, m;
    int s, f;

    cin >> n >> m;
    cin >> s >> f;

    vector<vector<edge>> graph(n+1);

    int b, e, w;

    for (int i = 0; i < m; i++){
        cin >> b >> e >> w;
        graph[b].emplace_back(w, e);
        graph[e].emplace_back(w, b);
    }

    BelmanFord(graph, s, f);



}
