#include <vector>
#include <iostream>
#include <deque>
using namespace std;

int main() {

    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> A(N, vector<int>(M));
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> A[i][j];

    vector<pair<int,int>> coins;
    vector<vector<int>> coin_id(N, vector<int>(M, -1));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(A[i][j] == 2) {
                coin_id[i][j] = coins.size();
                coins.emplace_back(i,j);
            }
        }
    }
    int C = coins.size();
    int FULL = 1 << C;

    const int INF = 1e9;
    vector<vector<vector<int>>> dist(
        N, vector<vector<int>>(M, vector<int>(FULL, INF))
    );

    int start_mask = 0;
    if(coin_id[0][0] != -1)
        start_mask |= 1 << coin_id[0][0];

    deque<tuple<int,int,int>> q;
    dist[0][0][start_mask] = 0;
    q.emplace_back(0, 0, start_mask);

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while(!q.empty()){
        auto [x,y,mask] = q.front(); 
        q.pop_front();
        int d = dist[x][y][mask];
        if(d == K) continue;
        for(int dir = 0; dir < 4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if(nx<0||nx>=N||ny<0||ny>=M) continue;
            if(A[nx][ny] == 1) continue;

            int new_mask = mask;
            if(coin_id[nx][ny] != -1){
                new_mask |= 1 << coin_id[nx][ny];
            }
            if(dist[nx][ny][new_mask] > d+1){
                dist[nx][ny][new_mask] = d+1;
                q.emplace_back(nx, ny, new_mask);
            }
        }
    }


    int answer = -1;
    for(int mask = 0; mask < FULL; mask++){
        if(dist[N-1][M-1][mask] <= K){
            int cnt = __builtin_popcount(mask);
            answer = max(answer, cnt);
        }
    }

    cout << answer << endl;
    return 0;
}