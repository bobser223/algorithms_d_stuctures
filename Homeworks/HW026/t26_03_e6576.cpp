#include <vector>
#include <iostream>
#include <map>
#include <stack>

#define SHIT_RETURN -100500
#define SOMETHING 100500
#define MINIMUM -10050000


using std::map;
using std::vector;


struct Item{
    int position, priority;

    Item() = default;

    Item(int pos, int prior): position(pos), priority(prior) {}
    Item(size_t pos, int prior): position(pos), priority(prior) {}

};




class min_heap{
private:
    vector<int> heap;
    map<int, Item> items;
    size_t heap_size;

    int get_min_child(int parent){
        int left  = parent*2;
        int right = parent*2 + 1;
        if (right > (int)heap_size)
            return left;
        return (items[heap[left]].priority < items[heap[right]].priority
                ? left : right);
    }

    void swap_nodes(int i, int j) {
        int key_i = heap[i], key_j = heap[j];
        std::swap(heap[i], heap[j]);
        items[key_i].position = j;
        items[key_j].position = i;
    }

    void sift_up(int curr){
        while(curr != 1){
            int parent = curr / 2;

            if (items[heap[parent]].priority > items[heap[curr]].priority){
                swap_nodes(curr, parent);

                curr = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(int curr){


        while(curr*2 <= heap_size){
            int min_child = get_min_child(curr);
            if (items[heap[curr]].priority > items[heap[min_child]].priority ){
                swap_nodes(curr, min_child);
                curr = min_child;
            } else {
                break;
            }
        }
    }


public:
    min_heap(){
        heap_size = 0;
        heap.push_back(SOMETHING);
    }

    min_heap(std::initializer_list<std::pair<int, int>>& il){
        heap.push_back(SOMETHING);
        heap_size = 0;
        for (auto& [key, priority]: il)
            push(key, priority);
    }

    void push(int key, int priority){
        if (!contains(key)) {
            heap.push_back(key);
            heap_size++;
            items[key] = {heap_size, priority};
            sift_up(static_cast<int>(heap_size));
        } else {
//            update_priority(key, priority);
            if (priority < items[key].priority) {
                update_priority(key, priority);
            }
        }
    }

    std::pair<int,int> extract_min() {
        if (heap_size == 0) return {SHIT_RETURN, SOMETHING};

        int key = heap[1];
        int pr  = items[key].priority;


        swap_nodes(1, heap_size);
        heap.pop_back();
        items.erase(key);
        --heap_size;
        sift_down(1);

        return {key, pr};
    }


    int get_minimum(){
        if (heap_size){

            int min_key = heap[1];
            swap_nodes(1, heap_size);
            heap.pop_back();
            items.erase(min_key);
            heap_size--;
            sift_down(1);
            return min_key;

        }
        return SHIT_RETURN;
    }

    bool contains(int key){
        return items.find(key) != items.end();
    }

    [[nodiscard]] int get_priority(int key) {
        if (contains(key))
            return items.at(key).priority;
        else
            return MINIMUM;
    }

    void update_priority(int key, int new_priority){
        int old_priority = items[key].priority;
        items[key].priority = new_priority;

        if (old_priority < new_priority){
            sift_down(items[key].position);
        } else {
            sift_up(items[key].position);
        }
    }

    [[nodiscard]] bool empty() const{ return heap_size == 0;}
};


#define sz size_t

using namespace std;

struct Edge{
    int to, weight;
};

class Graph{
private:
    vector<vector<Edge>> graph;
    size_t size;
    bool oriented;
public:
    explicit Graph(size_t _size, bool _oriented=false): size(_size), oriented(_oriented){
        graph.resize(_size+1); // 1 - based;
    }

    void add(int from, int to, int  weight){

        graph[from].emplace_back(to, weight);
        if (!oriented){
            graph[to].emplace_back(from, weight);
        }
    }

    vector<vector<Edge>> get_container(){
        return graph;
    }

    void prim(int p, int _q){
        vector<int> parent(size+1, -1);
        int total_weight = 0;

        size_t processed_cnt = 0;
        min_heap pq;
        pq.push(p, 0);
        vector<bool> used(size+1, false);


        while(!pq.empty() && processed_cnt < size){
            auto [v_min, w_min] = pq.extract_min();

            used[v_min] = true;
            processed_cnt++;
            total_weight += w_min;

            for (auto [neighbour, weight]: graph[v_min]){
                if (used[neighbour])
                    continue;

                // якщо вершини ще немає в купі, або нова вага краща за стару
                if (!pq.contains(neighbour) || weight < pq.get_priority(neighbour)) {
                    pq.push(neighbour, weight);
                    parent[neighbour] = v_min;
                }
            }
        }

        if (parent[p] == _q || parent[_q] == p)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }


};

void in_loop(){
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    Graph g(n);

    int u, v, w;
    for (int i = 0; i < m; i++){
        cin >> u >> v >> w;
        g.add(u, v, w);
    }
    g.prim(p, q);
}


int main(){
    int t;
    cin >> t;
    for (int _ = 0; _ < t; _++){
        in_loop();
    }
}