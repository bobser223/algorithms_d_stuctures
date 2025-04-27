#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
    int n, m, b1, b2;

    cin >> n >> m;

    vector<set<int>> vec(n);

    for (int i = 0; i < m; i++){
        cin >> b1 >> b2;
        vec[--b1].insert(b2);

    }

    int check = n*(n-1)/2;
    int sum = 0;

    for (int i = 0; i < n; i++){
        sum += vec[i].size();
    }

    if (sum != check){
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
}