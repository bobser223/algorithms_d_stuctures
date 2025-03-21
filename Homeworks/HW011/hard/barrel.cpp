#include <iostream>
#include <set>

int* barrels;
int* bl;
int n, m;

using namespace std;

set<int> result;


void solution(int left, int balance, int i, int curr_barr){
    if (i == m){
        if (balance == 0){
            result.insert(left*2 + curr_barr);
        }
        return;
    }

    solution(left, balance, i+1, curr_barr);
    solution(left+bl[i], balance + bl[i], i+1, curr_barr );
    solution(left, balance - bl[i], i+1, curr_barr );
}


int main(){
    cin >> n >> m;

    barrels = new int[n];
    bl = new int[m];

    for (int i = 0; i < n; i++){
        cin >> barrels[i];
    }

    for (int i = 0; i < m; i++){
        cin >> bl[i];
    }

    for (int i = 0; i < n; i++){
        solution(0, 0, 0, barrels[i]);
    }


    for (int value: result){
        cout << value << endl;
    }


    delete [] barrels;
    delete [] bl;
}