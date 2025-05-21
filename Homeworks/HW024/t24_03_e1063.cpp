#include <iostream>
#include <vector>
#include <queue>

#define let auto

using namespace std;
struct Coord{
    int x, y;
    Coord() = default;
    Coord(int a, int b): x(a), y(b) {}
    ~Coord() = default;
    Coord& operator = (const Coord& other){
        if(this != &other){
            this->x = other.x;
            this->y = other.y;
        }
        return *this;
    }

    bool operator ==(const Coord& other) const {
        return this->x == other.x && this->y == other.y;
    }
};


void BFS(int x_input, int y_input, const vector<vector<char>>& maze, vector<vector<bool>>& visited){
    int n = maze.size(), m = maze[0].size();


    vector<Coord> directions = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    queue<Coord> q;

    q.emplace(x_input, y_input);

    visited[x_input][y_input] = true;

    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();

        for (auto& [i, j]: directions){
            int xi = x+i;
            int yj = y+j;

            if (xi < 0 || xi >= n || yj < 0 || yj >= m)
                continue;

            if (maze[xi][yj] == '#' && !visited[xi][yj]){
                visited[xi][yj] = true;
                q.emplace(xi, yj);
            }
        }
    }

}

void pieces_count(const vector<vector<char>>& maze){
    int n = maze.size();
    int m = maze[0].size();

    size_t counter = 0;

    vector<vector<bool>> visited(n, std::vector<bool>(m, false));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (maze[i][j] != '.' && !visited[i][j]){
                counter++;
                BFS(i, j, maze, visited);

            }

        }
    }

    std:: cout << counter << std::endl;






}



int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> maze(n, std::vector<char>(m));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> maze[i][j];
        }
    }

    pieces_count(maze);

}