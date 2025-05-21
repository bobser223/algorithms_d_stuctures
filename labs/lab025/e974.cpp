#include <iostream>
#include <vector>
#include <stack>


#define INF 100

using namespace std;


int main(){
    int n;
    cin >> n;
    vector<vector<int>> graph(n, std::vector<int>(n, INF));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> graph[i][j];
        }
    }

    vector<vector<int>> dist(n, std::vector<int>(n, INF));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                if (i == j) dist[i][j] = 0;
                if (dist[i][j] > INF) dist[i][j] = INF;
            }

        }


    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] >= INF/2)
                cout << "INF ";
            else
                cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;



}