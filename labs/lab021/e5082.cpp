#include <iostream>
using namespace std;


int main(){
    int n, buff;
    cin>>n;
//    vector<int> vert;

    for (int i = 0; i < n; i++){
        int sum = 0;
        for (int j = 0; j < n; j++){
            cin >> buff;
            sum += buff;
        }
        cout << sum << " ";

    }
}

