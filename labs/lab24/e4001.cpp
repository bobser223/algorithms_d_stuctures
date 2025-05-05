#include <vector>
#include <iostream>
#include <queue>

#define WALL '*'
#define CELL  '.'

#define VISITED 1
#define EMPTY 0

using namespace std;

struct coord{
    int x;
    int y;
};

vector<coord> DIRECTIONS = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int wave(std::vector<std::vector<char>>& maze,int n, int si, int sj){
    int count = 0;
    std::vector<std::vector<int>> visited(n, std::vector<int>(n, EMPTY));
    visited[si][sj] = VISITED;
    std::queue<coord> q;
    q.push({si, sj});

    while (!q.empty()){
        auto [i, j] = q.front(); q.pop();
        count++;
        for (auto [di, dj] : DIRECTIONS){
            int ni = i+di;
            int nj = j + dj;
            if (maze[ni][nj] == CELL && !(visited[ni][nj])){
                visited[ni][nj] = VISITED;
                q.push({ni, nj});
            }
        }
    }

    return count;

}


int main(){
    std::vector vec{"c"};
    std::vector vec_2{1, 2, 3};

    int n, si, sj;
    cin >> n;
    std::vector<std::vector<char>> room(n, std::vector<char>(n, CELL));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> room[i][j];
        }
    }


    cin >> si >> sj;
    --si;
    --sj;
    cout << wave(room, n, si, sj) << endl;

}

