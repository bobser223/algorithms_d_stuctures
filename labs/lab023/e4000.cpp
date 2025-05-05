#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;
int n, s;


int bfs(vector<vector<int>> graph, int vertex){
    stack<int> st;
    set<int> visited;
    int count = 1;
    st.push(vertex-1);
    visited.insert(vertex-1);

    while(!st.empty()){
        int curr = st.top(); st.pop();

        for (int i = 0; i < n; i++){
            if (graph[curr][i] != 0){
                if (visited.find(i) == visited.end()){
                    count++;
                    visited.insert(i);
                    st.push(i);
                }
            }
        }
    }
    return count;

}


int main(){

    cin >> n >> s;

    vector<vector<int>> graph(n, vector<int>(n, 0));


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> graph[i][j];
        }
    }

    cout << bfs(graph, s);


}
