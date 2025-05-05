#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

class graph {
private:
    std::vector<std::set<int>> container;
public:
    explicit graph(int n) {
        container.resize(n + 1);
    }

    ~graph() = default;

    void add(int v, int e) {
        container[v].insert(e);
        container[e].insert(v);
    }

    std::vector<int> bfs(const std::vector<int>& starts){
        std::vector<int> dist(container.size(), -1);
        std::queue<int> q;

        for (int s: starts){
            q.push(s);
            dist[s] = 0;
        }

        while(!q.empty()){
            int curr = q.front(); q.pop();

            for (int neighbour: container[curr]){
                if (dist[neighbour] == -1){
                    dist[neighbour] = dist[curr] + 1;
                    q.push(neighbour);
                }
            }
        }

        return dist;
    }
};


int main(){
    int n, m, k;
    std::cin >> n >> m;

    graph g(n);

    for(int i = 0; i < m; i++){
        int b1, b2;
        std::cin >> b1 >> b2;
        g.add(b1, b2);
    }

    std::cin >> k;
    std::vector<int> starts(k);
    for (auto& var: starts)
        std::cin >> var;

    auto dist = g.bfs(starts);

    int max = *std::max_element(dist.begin(), dist.end());
    std::cout << max << std::endl;
    for (int i = 1; i < n+1; i++){
        if (dist[i] == max){
            std::cout << i << std::endl;
            return 0;
        }
    }


}