#include <iostream>
using namespace std;


int main(){
    int n, buff;
    cin>>n;
//    vector<int> vert;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> buff;
            if (buff){
                cout << i+1 << " " << j+1 << endl;
            }
        }

    }
}

