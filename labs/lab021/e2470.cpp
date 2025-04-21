#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> A(n, vector<int>(n));


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }


    for (int i = 0; i < n; i++) {
        if (A[i][i] != 0) {
            cout << "NO\n";
            return 0;
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i][j] != A[j][i] || (A[i][j] != 0 && A[i][j] != 1)) {
                cout << "NO\n";
                return 0;
            }
        }
    }


    cout << "YES\n";
    return 0;
}
