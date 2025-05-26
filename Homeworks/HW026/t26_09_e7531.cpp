#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <climits>

using namespace std;

struct Edge {
    int to;
    int weights;

    friend std::istream& operator>>(std::istream& is, Edge& n);
};

std::istream& operator>>(std::istream& is, Edge& n) {
    is >> n.to >> n.weights;
    return is;
}
struct CompareEdge {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.weights > b.weights;
    }
};

class Graph{
private:
    vector<vector<Edge>> graph;
    size_t g_size;
    bool oriented;
public:
    explicit Graph(size_t _size, bool _oriented=false): g_size(_size), oriented(_oriented){
        graph.resize(_size+1); // 1 - based;
    }

    void add(int from, int to, int  weight){

        graph[from].emplace_back(to, weight);
        if (!oriented){
            graph[to].emplace_back(from, weight);
        }
    }

    vector<vector<Edge>> get_container() const {
        return graph;
    }

    size_t size() const {
        return g_size;
    }

    const vector<Edge>& operator[] (size_t idx){
        if (idx < 1 || idx > g_size) return {};
        return graph[idx];

    }


};



void prim_for_safe(const Graph& g, const set<int>& unsafe){
    size_t safe_cnt = g.size() - unsafe.size();
    auto graph = g.get_container();
    int n = g.size();

    int start = -1;
    for (int v = 1; v <= g.size(); ++v) { // пошук з якої стартонути (1 може бути закритою)
        if (!unsafe.count(v)) { start = v; break; }
    }
    if (start == -1){
        if (n == 1) {
            cout << 0 << "\n";
        }
        else if (n == 2) {
            // шукаємо ребро між 1 та 2
            bool found = false;
            int w = 0;
            for (auto &e : graph[1]) {
                if (e.to == 2) {
                    found = true;
                    w = e.weights;
                    break;
                }
            }
            if (found) cout << w << "\n";
            else       cout << "impossible\n";
        }
        else {
            cout << "impossible\n";
        }
        return;
    }

    vector<bool> used(g.size()+1, false);
    used[start] = true;
    size_t processed_cnt = 1;
    long long total_weight = 0;

    priority_queue<Edge,std::vector<Edge>, CompareEdge> pq;



    for (auto& e: graph[start]){
        if (!unsafe.contains( e.to))
            pq.push(e);


    }

    while(!pq.empty() && processed_cnt < g.size()){
        auto [v_min, w_min] = pq.top(); pq.pop();
        if (used[v_min]) continue;

        used[v_min] = true;
        processed_cnt++;
        total_weight += w_min;



        for (auto [neighbour, weight]: graph[v_min]){
            if (!used[neighbour] && !unsafe.contains(neighbour)){
                pq.emplace(neighbour, weight);
            }
        }
    }


    if (processed_cnt < safe_cnt) {
        cout << "impossible\n";
        return;
    }

    long long extra = 0;
    for (int d : unsafe) {
        int best = INT_MAX;
        for (auto &e : graph[d]) {
            if (!unsafe.count(e.to))
                best = min(best, e.weights);
        }
        if (best == INT_MAX) {
            cout << "impossible\n";
            return;
        }
        extra += best;
    }
    cout << total_weight + extra << "\n";
}


int main(){
    int n, m, p;
    cin >> n >> m >> p;
    Graph g(n);

    set<int> unsafe_houses;

    int buffer;
    for (int i = 0; i < p; i++){
        cin>>buffer;
        unsafe_houses.insert(buffer);
    }

    int x, y, l;
    for(int i = 0; i < m; i++){
        cin >> x >> y >> l;
        g.add(x, y, l);
    }

    prim_for_safe(g, unsafe_houses);
}