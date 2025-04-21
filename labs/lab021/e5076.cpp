#include <iostream>

using namespace std;


int main(){
    int n, m, buff1, buff2;
    cin >> n >> m;

    vector<int> vec(n);

    while (n-- ){
        cin >> buff1 >> buff2;
        vec[buff1 -1]++;
        vec[buff2 -1]++;
    }

    int v = vec[0];
    for (int var: vec){
        if (var != v){
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";


}