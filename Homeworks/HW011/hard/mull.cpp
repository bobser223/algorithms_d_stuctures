#include <iostream>
#include <string>
#include <cmath>
#include <utility>


typedef long long ll;




using namespace std;

string* memo;
ll memo_size;

struct pair_hash {
    std::size_t operator()(const std::pair<std::string, std::string>& p) const {
        return std::hash<std::string>{}(p.first) ^ (std::hash<std::string>{}(p.second) << 1);
    }
};

ll memo_position(string x, string y){
    pair<string, string> p(x, y);
    pair_hash ph;
    ll ca = ph(p);
    return ca;
}

string res(string x, string y){
    return memo[memo_position(x, y) % (memo_size +2)];
}

void set_res(string x, string y, string value){
    memo[memo_position(x, y) % (memo_size +2)] = value;
}

string karatsuba(string X, string Y){

    if(res(X, Y) != "-1"){
        return res(X, Y);
    }

    ll X_size = X.size();
    ll Y_size = Y.size();

    if (X_size == 1 || Y_size == 1)
        return to_string(stoll(X) * stoll(Y));

    ll n = max(X_size, Y_size);
    if (X_size < n) X = (string(n - X_size, '0') + X);
    if (Y_size < n) Y = (string(n - Y_size, '0') + Y);

    int m = n / 2;

    string A = X.substr(0, n-m);
    string B = X.substr(n - m);
    string C = Y.substr(0, n-m);
    string D = Y.substr(n - m);

    string AC = karatsuba(A, C);
    string BD = karatsuba(B, D);

    string AplusB = to_string(stoll(A) + stoll(B));
    string CplusD = to_string(stoll(C) + stoll(D));
    string middle = karatsuba(AplusB, CplusD);

    // Compute (A+B)(C+D) - AC - BD to get (AD + BC)
    ll middleInt = stoll(middle) - stoll(AC) - stoll(BD);

    string result = to_string(stoll(AC) * pow(10, 2 * m) + middleInt * pow(10, m) + stoll(BD));

    set_res(X, Y, result);

    return result;




}



int main(){
    string X, Y;
    cin >> X >> Y;

    memo = new string[stoll(X)*stoll(Y) + 1];
    memo_size = stoll(X)*stoll(Y) + 1;
    for (int i = 0; i < stoll(X)*stoll(Y) + 1; i++){
        memo[i] = "-1";
    }

    cout << karatsuba(X, Y) << endl;



}