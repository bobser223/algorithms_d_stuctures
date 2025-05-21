#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define EMPTY -1

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


void print_matrix(const std::vector<std::vector<char>>& matrix){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            cout << matrix[i][j];
        }
        cout << endl;
    }
}



void wave(std::vector<std::vector<char>>& maze,const Coord& start, const Coord& end){
    int n = maze.size();
    std::vector<std::vector<int>> wave_matrix(n, std::vector<int>(n, EMPTY));
    std::vector<std::vector<Coord>> sources(n, std::vector<Coord>(n));
    wave_matrix[start.x][ start.y] = 0;
    vector<Coord> directions = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    queue<Coord> q;
    q.push(start);

    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        for (auto [i, j]: directions){
            int x1 = x+i;
            int y1 = y+j;

            if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n)
                continue;

            if ((maze[x1][y1] == '.' || maze[x1][y1] == 'X') && wave_matrix[x1][y1] == EMPTY){
                q.emplace(x1, y1);
                wave_matrix[x1][y1] = wave_matrix[x][y] + 1;
                sources[x1][y1] = {x, y};
            }
        }
    }

    if (wave_matrix[end.x][end.y] == EMPTY){
        cout << "N" << endl;
        return;
    }

    Coord curr = {end.x, end.y};
    while (curr != start){
        maze[curr.x][curr.y] = '+';
        curr = sources[curr.x][curr.y];
    }

    cout << "Y" << endl;
    print_matrix(maze);

}



int main(){
    int n;
    cin >> n;

    Coord start, end;

    vector<vector<char>> maze(n, std::vector<char>(n));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> maze[i][j];
            if (maze[i][j] == '@')
                start = {i, j};


            if (maze[i][j] == 'X')
                end = {i, j};
        }
    }

    wave(maze, start, end);
}
