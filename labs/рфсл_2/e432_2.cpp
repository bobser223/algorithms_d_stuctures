#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define EMPTY -1

struct Coord {
    int x, y, z;
    Coord() = default;
    Coord(int a, int b, int c): x(a), y(b), z(c) {}
    bool operator==(const Coord& o) const {
        return x==o.x && y==o.y && z==o.z;
    }
};

void wave(vector<vector<vector<char>>>& maze, const Coord& S, const Coord& E) {
    int L = maze.size();
    int R = maze[0].size();
    int C = maze[0][0].size();
    vector<vector<vector<int>>> d(L, vector<vector<int>>(R, vector<int>(C, EMPTY)));
    queue<Coord> q;

    d[S.x][S.y][S.z] = 0;
    q.push(S);


    const Coord dirs[6] = {
            {1,0,0}, {-1,0,0},
            {0,1,0}, {0,-1,0},
            {0,0,1}, {0,0,-1}
    };

    while (!q.empty()) {
        auto u = q.front(); q.pop();
        if (u == E) {
            cout << "Escaped in " << d[u.x][u.y][u.z] << " minute(s).\n";
            return;
        }
        for (auto& dir : dirs) {
            int nx = u.x + dir.x;
            int ny = u.y + dir.y;
            int nz = u.z + dir.z;
            if (nx<0||nx>=L||ny<0||ny>=R||nz<0||nz>=C) continue;
            if (maze[nx][ny][nz]=='#' || d[nx][ny][nz]!=EMPTY) continue;
            d[nx][ny][nz] = d[u.x][u.y][u.z] + 1;
            q.push({nx,ny,nz});
        }
    }

    cout << "Trapped!\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int L,R,C;
        cin >> L >> R >> C;
        if (L==0 && R==0 && C==0) break;

        vector<vector<vector<char>>> maze(L, vector<vector<char>>(R, vector<char>(C)));
        Coord S,E;
        for (int i=0; i<L; i++) {
            for (int r=0; r<R; r++) {
                for (int c=0; c<C; c++) {
                    cin >> maze[i][r][c];
                    if (maze[i][r][c]=='S') S = {i,r,c};
                    if (maze[i][r][c]=='E') E = {i,r,c};
                }
            }
        }

        wave(maze, S, E);
    }

    return 0;
}
