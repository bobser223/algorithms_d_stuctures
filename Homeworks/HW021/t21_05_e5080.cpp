#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, buff, result=0;
    cin >> n;
    for(int i = 0; i < n; i++){
        int row_sum = 0;
        for(int j = 0; j < n; j++){
            cin >> buff;
            row_sum += buff;
        }
        if (row_sum == 1)
            result += 1;

    }
    cout << result << endl;
}
