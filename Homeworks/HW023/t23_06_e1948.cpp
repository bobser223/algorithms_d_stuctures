#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2


bool has_cycle = false;
vector<vector<int>> graph;

void dfs(int id, vector<int>& vec, stack<int>& st){
    if (has_cycle) return;
    if (vec[id] == GRAY){
        has_cycle = true;
        return;
    }

    if (vec[id] == BLACK) return;

    vec[id] = GRAY;

    for (int i: graph[id])
            dfs(i, vec, st);


    vec[id] = BLACK;
    st.push(id);

}




int main(){
    int n, m, b1, b2;
    cin >> n >> m;
    graph.resize(n+1);

    for(int i = 0; i < m; i++){
        cin >> b1 >> b2;
        graph[b1].push_back(b2);
    }


    std::vector<int> vec(n+1, WHITE);
    std::stack<int> st;

    for(int id = 1; id <= n; id++){
        dfs(id, vec, st);
    }


    if (has_cycle){
        std::cout << -1 << endl;
        return 0;
    }

    while(!st.empty()){

        cout << st.top() << " ";
        st.pop();
    }
}