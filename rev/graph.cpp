#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;


class GraphAdjacencyList{
private:
    void do_sth(int vertex){}

    bool is_oriented;
    vector<vector<int>> neighbors;
    int g_size;

public:
    explicit GraphAdjacencyList(int size, bool oriented=false){
        // вершини починаються з нуля, якщо з одиниці, то тоді resize(size + 1) та neighbors[0] завжди пустий
        neighbors.resize(size);
        is_oriented = oriented;
        g_size = size;
    }

    ~GraphAdjacencyList() = default;


    void add(int vertex, int edge){
        neighbors[vertex].push_back(edge);
        if (!is_oriented)
            neighbors[edge].push_back(vertex);

    }

    void removeEdge(int vertex, int edge){
        neighbors[vertex].erase(
            std::remove(neighbors[vertex].begin(), neighbors[vertex].end(), edge),
            neighbors[vertex].end()
        );
        if (!is_oriented)
            neighbors[edge].erase(
                std::remove(neighbors[edge].begin(), neighbors[edge].end(), vertex),
                neighbors[edge].end()
            );
    }



    void DFS(int vertex){
        do_sth(vertex);

        stack<int> st;
        st.push(vertex);

        vector<bool> used(g_size, false);
        used[vertex] = true;

        while(!st.empty()){
            int curr = st.top(); st.pop();

            for (int neighbor: neighbors[curr]){
                if (!used[neighbor]){
                    do_sth(neighbor);
                    st.push(neighbor);
                    used[neighbor] = true;
                }
            }
        }

    }


    void BFS(int vertex){
        do_sth(vertex);

        queue<int> q;
        q.push(vertex);

        vector<bool> used(g_size, false);
        used[vertex] = true;

        while(!q.empty()){
            int curr = q.front(); q.pop();
            for (int neighbor: neighbors[curr]){
                if (!used[neighbor]){
                    do_sth(neighbor);
                    q.push(neighbor);
                    used[neighbor] = true;
                }
            }

        }
    }


};


class GraphMatrix{
private:
    void do_sth(int vertex){}
    vector<vector<int>> matrix;
    int g_size;
    bool is_oriented;
public:
    explicit GraphMatrix(int size, bool oriented=false){
        g_size = size;
        matrix.resize(size, std::vector(size, 0));
        is_oriented = oriented;
    }

    ~GraphMatrix() = default;

    void add(int vertex, int edge){
        // якщо вершини рахуємо з 1 то тут варто зробити vertex--; edge--;
        matrix[vertex][edge] = 1;
        if (!is_oriented){
            matrix[edge][vertex] = 1;
        }
    }

    void removeEdge(int vertex, int edge){
        // якщо вершини рахуємо з 1 то тут варто зробити vertex--; edge--;
        matrix[vertex][edge] = 0;

        if (!is_oriented){
            matrix[edge][vertex] = 0;
        }
    }

    void DFS(int vertex){
        // якщо вершини рахуємо з 1 то тут варто зробити vertex--;
        do_sth(vertex);

        stack<int> st;
        st.push(vertex);

        vector<bool> used(g_size, false);
        used[vertex] = true;

        while(!st.empty()){
            int curr = st.top(); st.pop();

            for (int neighbor = 0; neighbor < g_size; neighbor++){
                if (matrix[curr][neighbor] == 1 && !used[neighbor]){
                    do_sth(neighbor);
                    st.push(neighbor);
                    used[neighbor] = true;
                }
            }
        }
    }

    void BFS(int vertex){
        // якщо вершини рахуємо з 1 то тут варто зробити vertex--;
        do_sth(vertex);

        queue<int> q;
        q.push(vertex);

        vector<bool> used(g_size, false);
        used[vertex] = true;

        while(!q.empty()){
            int curr = q.front(); q.pop();

            for (int neighbor = 0; neighbor < g_size; neighbor++){
                if (matrix[curr][neighbor] == 1 && !used[neighbor]){
                    do_sth(neighbor);
                    q.push(neighbor);
                    used[neighbor] = true;
                }
            }
        }
    }





};