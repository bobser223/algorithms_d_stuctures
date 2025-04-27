#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


bool is_in(const vector<int>& vec, int value){
    auto it = std::find(vec.begin(), vec.end(), value);
    if (it == vec.end()) return false;
    return true;
}

int main(){
    int n, m, b1, b2;

    cin >> n >> m;
    vector<vector<int>> vec(n);

    for (int i = 0; i < m; i++){
        cin >> b1 >> b2;
        if(is_in(vec[b1-1], b2)){
            cout << "YES" << endl;
            return 0;
        }
        vec[b1-1].push_back(b2);
    }

    cout << "NO" << endl;

}