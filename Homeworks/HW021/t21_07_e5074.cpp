#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m, b1, b2;
    cin >> n >> m;

    vector<int> vec(n, 0);

    for(int i = 0; i < m; i++){
        cin >> b1 >> b2;
        vec[--b1]++; vec[--b2]++;
    }

    for(auto var: vec){
        cout << var << endl;
    }

}