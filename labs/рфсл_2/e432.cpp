#include <iostream>
#include <vector>
#include <queue>

using namespace std;


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define EMPTY -1

struct Coord{
    int x, y, z;
    Coord() = default;
    Coord(int a, int b, int c): x(a), y(b), z(c) {}
    ~Coord() = default;
    Coord& operator = (const Coord& other){
        if(this != &other){
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }
        return *this;
    }

    bool operator ==(const Coord& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }
};



void wave(std::vector<std::vector<std::vector<char>>>& maze_list,const Coord& start, const Coord& end){
    int L = maze_list.size();
    int R = maze_list[0].size();
    int C = maze_list[0][0].size();
    std::vector<std::vector<std::vector<int>>> wave_matrix(L, std::vector<std::vector<int>>(R, std::vector<int>(C, EMPTY)));
    wave_matrix[start.z][ start.x][start.y] = 0;

    vector<Coord> directions  = {
            { 0,  1,  0}, // вниз/південь по рядку
            { 0, -1,  0}, // вгору/північ по рядку
            { 0,  0,  1}, // вправо/схід по стовпцю
            { 0,  0, -1}, // вліво/захід по стовпцю
            { 1,  0,  0}, // «вгору» по рівню
            {-1,  0,  0}, // «вниз» по рівню
    };

    queue<Coord> q;
    q.push(start);

    while(!q.empty()){
        auto [x, y, z] = q.front(); q.pop();
        for (auto [i, j, jj]: directions){
            int x1 = x+i;
            int y1 = y+j;
            int z1 = z + jj;

            if (x1 < 0 || x1 >= R || y1 < 0 || y1 >= C || z1 < 0 || z1 >= L)
                continue;

            if ((maze_list[z1][x1][y1] == '.' || maze_list[z1][x1][y1] == 'E') && wave_matrix[z1][x1][y1] == EMPTY){
                q.emplace(x1, y1, z1);
                wave_matrix[z1][x1][y1] = wave_matrix[z][x][y] + 1;
            }
        }
    }

    if (wave_matrix[end.z][end.x][end.y] == EMPTY){
        cout << "Trapped!" << endl;
        return;
    }

    cout << "Escaped in " << wave_matrix[end.z][end.x][end.y] << " minute(s)." << endl;

}



int main(){
    while(true){
        int L, R, C;
        cin >> L >> R >> C;

        if (L == 0 && R== 0 && C== 0){
            break;
        }

        Coord start, end;

        vector<vector<vector<char>>> maze_list(L);
        for (int i = 0; i < L; i++){
            vector<vector<char>> maze(R, std::vector<char>(C));
            for (int ii = 0; ii < R; ii++){
                for (int iii = 0; iii < C; iii++){
                    cin >> maze[ii][iii] ;
                    if (maze[ii][iii] == 'S'){
                        start = {i, ii, iii};
                    }
                    if (maze[ii][iii] == 'E'){
                        end = {i, ii, iii};
                    }
                }
            }
            maze_list[i] = maze;

        }
        wave(maze_list, start, end);
    }



}
