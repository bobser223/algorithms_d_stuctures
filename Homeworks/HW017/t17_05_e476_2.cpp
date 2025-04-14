#include <iostream>
#include <fstream>

typedef long long ll;


int main(){
    std::ifstream fin("input.txt");

    ll prev;
    ll min = LLONG_MIN;
    ll max = LLONG_MAX;

    ll x;

    bool flag = true;
    fin >> prev;

    while(fin >> x){
        if (x <= min || x >= max){
            flag = false;
            break;
        }

        if (x < prev){
            max = prev;
        } else {
            min = prev;
        }

        prev = x;
    }

    std::cout << (flag? "YES\n": "NO\n");

}