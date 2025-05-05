#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>

#define IN(c, x) ((c).find(x) != (c).end())


class graph{
private:
    std::vector<std::set<int>> container;
public:
    explicit graph(int n){
        container.resize(n+1);
    }
    ~graph() = default;

    void add(int v, int e){
        container[v].insert(e);
    }

//    void dfs(int start, int finish){
//        std::set<int> used;
//        std::stack<int> st;
//        int counter = 0;
//
//
//        st.push(start);
//        while(!st.empty()){
//            int curr = st.top(); st.pop();
//            for(auto neighbour: container[curr]){
//                if (used.find(neighbour) != used.end()){
//                    st.push(neighbour);
//                    if (neighbour == finish)
//                        counter++;
//                    else
//                        used.insert(neighbour);
//                }
//            }
//        }
//
//
//    }

    void dfs(int u, int target, int days_left, std::vector<bool>& visited, int& counter) {
        if (days_left == 0) return;
        for (int v : container[u]) {
            if (!visited[v]) {

                if (v == target) {
                    ++counter;
                }
                if (days_left > 1) {
                    visited[v] = true;
                    dfs(v, target, days_left - 1, visited, counter);
                    visited[v] = false;
                }
            }
        }
    }

    long long countPaths(int start, int target, int maxDays) {
        int counter = 0;
        std::vector<bool> visited(container.size(), false);
        visited[start] = true;
        dfs(start, target, maxDays, visited, counter);
        return counter;
    }
};




int main(){
    int n, k, a, b, d;
    std::cin >> n >> k >> a >> b >> d;

    graph g(n);

    for(int i = 0; i < k; i++){
        int b1, b2;
        std::cin >> b1 >> b2;
        g.add(b1, b2);
    }

    std::cout << g.countPaths(a, b, d);

}



