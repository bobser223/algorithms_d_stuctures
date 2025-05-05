#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

std::vector<std::set<int>> graph;
std::vector<bool> visited;

void bfs(){
    stack<int> st;
    st.push(1);


    while(!st.empty()){
        int curr = st.top(); st.pop();

        for (int neighbour: graph[curr]){
            if (!visited[neighbour]){
                visited[neighbour] = true;
                st.push(neighbour);
            }
        }
    }

    for (bool var: visited){
        if (!var){
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;

}


int main(){
    int n, m, b1, b2;

    cin >> n >> m;

    graph.resize(n+1);
    visited.resize(n+1, false);
    visited[0] = true;


    for (int i = 0; i < m; i++){
        cin >> b1 >> b2;
        graph[b1].insert(b2);
        graph[b2].insert(b1);
    }

    bfs();

}

