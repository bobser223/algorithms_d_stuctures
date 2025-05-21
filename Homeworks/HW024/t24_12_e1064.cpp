#include <iostream>
#include <queue>
#include <vector>

using  namespace std;

void print_matrix(const std::vector<std::vector<char>>& matrix){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

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


void BFS(vector<vector<char>>& board, const Coord& start, const Coord& end){
    int n = board.size();
    vector<vector<bool>> visited(n, std::vector<bool>(n, false));
    vector<vector<Coord>> references (n, std::vector<Coord>(n));

    vector<Coord> directions = {
            {2, 1}, {2, -1},
            {-2, 1}, {-2, -1},
            {1, 2}, {1, -2},
            {-1, 2}, {-1, -2}
    };

    visited[start.x][start.y] = true;

    queue<Coord> q;

    q.push(start);

    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();

        for (auto [i, j]: directions){
            int xi = x + i;
            int yj = y + j;

            if (xi < 0 || yj < 0 || xi >= n || yj >= n)
                continue;

            if ((board[xi][yj] == '@' || board[xi][yj] == '.') && !visited[xi][yj]) {
                references[xi][yj] = {x, y};
                visited[xi][yj] = true;
                q.emplace(xi, yj);
            }

        }
    }

    if (!visited[end.x][end.y]){
        cout << "Impossible" << endl;
        return;
    }

    Coord curr = end;
    while(curr != start){
        board[curr.x][curr.y] = '@';
        curr = references[curr.x][curr.y];
    }

    print_matrix(board);


}

int main(){
    int n;
    cin >> n;

    int start_end_cnt = 0;

    Coord start, end;

    vector<vector<char>> board(n, std::vector<char>(n));

    for (int i = 0;i < n;i++){
        for (int j = 0; j < n; j++){
            cin >> board[i][j];
            if (board[i][j] == '@'){
                if (start_end_cnt == 0){
                    start = {i, j};
                    start_end_cnt++;
                } else {
                    end = {i, j};
                }
            }
        }
    }

    BFS(board, start, end);
}