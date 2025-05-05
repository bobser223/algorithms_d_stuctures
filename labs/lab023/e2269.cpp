#include <iostream>
#include <vector>
#include <stack>
#include <set>

int n;

using namespace std;


int bfs(vector<vector<int>> graph, int m){
    vector<bool> global_visited(m);
    int counter = 0;

    for (int i = 0; i < m; i++){
        if (!global_visited[i]){
            vector<bool> local_visited(m);
            stack<int> st;
            st.push(i);
            local_visited[i] = true;
            while(!st.empty()){
                int curr = st.top(); st.pop();

                for (int j = 0; j < m; j++){
                    if (graph[curr][j] && !local_visited[graph[curr][j]]){
                        st.push(j);
                        global_visited[graph[curr][j]] = true;
                        local_visited[graph[curr][j]] = true;
                    }
                }
            }
            counter++;
        }

    }

    return counter;
}

int main(){

    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> graph[i][j];
        }
    }

    cout << bfs(graph, n);


}