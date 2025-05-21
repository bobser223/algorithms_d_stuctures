#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define LAND_OR_VISITED true

#define WATER false


struct Coord{int x; int y;};

int BFS(int x_input, int y_input, vector<vector<bool>>& area){
    int counter = 0;

    int n = area.size(), m = area[0].size();

    queue<Coord> q;
    q.emplace(x_input, y_input);
    vector<Coord> directions = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    while (!q.empty()){
        auto [x, y] = q.front(); q.pop();

        for (auto [i, j]: directions){
            int xi = x + i;
            int yj = y + j;
            if (xi < 0 || xi >= n || yj < 0 || yj >= m)
                continue;
            if (area[xi][yj] == WATER){
                q.emplace(xi, yj);
                area[xi][yj] = LAND_OR_VISITED;
                counter++;
            }
        }
    }

    return counter;
}

int main(){
    int n, m, k, b1, b2;
    cin >> n >> m >> k;

    vector<vector<bool>> area(n, std::vector<bool>(m, LAND_OR_VISITED));


    for (int i = 0; i < k; i++){
        cin >> b1 >> b2;
        area[--b1][--b2] = WATER;
    }

    int max_count = 0;
    int curr_count = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){

            if (area[i][j] == WATER){
                curr_count = BFS(i, j, area);
                if (curr_count > max_count)
                    max_count = curr_count;
            }
        }

    }


    std::cout << max_count << std::endl;

}