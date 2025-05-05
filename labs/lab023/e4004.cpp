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

    for (int i = 0; i < vec.size(); i++){
        if (graph[id][i] == 1 ){
            dfs(i, vec, st);
        }
    }
    vec[id] = BLACK;
    st.push(id);


}


int main(){
    int n;
    cin >> n;
    graph.resize(n, std::vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> graph[i][j];
        }
    }


    std::vector<int> vec(n, WHITE);
    std::stack<int> st;
    for(int id = 0; id < n; id++){
        dfs(id, vec, st);
    }

    if (has_cycle){
        std::cout << 1 << endl;
        return 0;
    } else {
        cout << 0 << endl;
    }

//    while(!st.empty()){
//        cout << st.top() << " ";
//        st.pop();
//    }
}