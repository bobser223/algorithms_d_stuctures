#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <unordered_map>

#include <gmp.h>



typedef long long ll;
using namespace std;


class Number {
private:
    mpz_t num;
public:
    Number(string str){
        mpz_init(num);
        mpz_set_str(this->num, str.c_str(), 10);
    }

    Number(){
        mpz_init(num);
    }

    ~Number(){
        mpz_clear(this->num);
    }


    Number operator*(Number& other){
        Number result;
        mpz_mul(result.num, this->num, other.num);
        return result;
    }

    Number operator*(ll number){
        Number result;

        mpz_t mpz_number;
        mpz_init(mpz_number);
        mpz_set_si(mpz_number, number);

        mpz_mul(result.num, mpz_number, this->num);

        mpz_clear(mpz_number);

        return result;
    };

    Number operator+(Number other){
        Number result;
        mpz_add(result.num, this->num, other.num);
        return result;
    }

    Number operator+(ll number){
        Number result;

        mpz_t mpz_number;
        mpz_init(mpz_number);
        mpz_set_si(mpz_number, number);

        mpz_add(result.num, mpz_number, this->num);

        mpz_clear(mpz_number);

        return result;
    };

    Number operator-(Number& other){
        Number result;
        mpz_sub(result.num, this->num, other.num);
        return result;
    }

    Number operator-(ll number){
        Number result;

        mpz_t mpz_number;
        mpz_init(mpz_number);
        mpz_set_si(mpz_number, number);

        mpz_sub(result.num, mpz_number, this->num);

        mpz_clear(mpz_number);

        return result;
    };

    std::string get_string() {
        char* c_str = mpz_get_str(nullptr, 10, this->num);
        std::string result(c_str);
        free(c_str);
        return result;
    }


};

// Custom hash for pair<string, string>
struct pair_hash {
    std::size_t operator()(const std::pair<std::string, std::string>& p) const {
        return std::hash<std::string>{}(p.first) ^ (std::hash<std::string>{}(p.second) << 1);
    }
};

// Global unordered_map for memoization.
unordered_map<pair<string, string>, string, pair_hash> memo;

// Functions to access and update memoized results.
string res(string x, string y) {
    pair<string, string> key(x, y);
    if (memo.find(key) != memo.end())
        return memo[key];
    return "-1";
}

void set_res(string x, string y, string value) {
    pair<string, string> key(x, y);
    memo[key] = value;
}

string karatsuba(string X, string Y) {

    if (res(X, Y) != "-1") {
        return res(X, Y);
    }

    ll X_size = X.size();
    ll Y_size = Y.size();

    if (X_size == 1 || Y_size == 1)
        return to_string(stoll(X) * stoll(Y));

    ll n = max(X_size, Y_size);
    if (X_size < n) X = string(n - X_size, '0') + X;
    if (Y_size < n) Y = string(n - Y_size, '0') + Y;

    int m = n / 2;

    string A = X.substr(0, n - m);
    string B = X.substr(n - m);
    string C = Y.substr(0, n - m);
    string D = Y.substr(n - m);

    string AC = karatsuba(A, C);
    string BD = karatsuba(B, D);

    Number _A(A);
    Number _B(B);

    string AplusB = (_A + _B).get_string();

    Number _C(C);
    Number _D(D);

    string CplusD = (_C + _D).get_string();


//    string AplusB = to_string(stoll(A) + stoll(B));
//    string CplusD = to_string(stoll(C) + stoll(D));
    string middle = karatsuba(AplusB, CplusD);

    // Compute (A+B)(C+D) - AC - BD to get (AD + BC)

    Number _middle(middle);
    Number _AC(AC);
    Number _BD(BD);

    Number middleInt = _middle - _AC - _BD;

//    ll middleInt = stoll(middle) - stoll(AC) - stoll(BD);


    string result = ((_AC * (ll)(pow(10, 2 * m))) + (middleInt * (ll)(pow(10, m)) + _BD)).get_string();

//    string result = to_string(stoll(AC) * static_cast<ll>(10, 2 * m) + middleInt * static_cast<ll>(10, m) + stoll(BD));

    set_res(X, Y, result);

    return result;
}

int main(){
    string X, Y;
    cin >> X >> Y;
    std::string s = karatsuba(X, Y);
    size_t pos = s.find('.');
    std::string result = (pos != std::string::npos) ? s.substr(0, pos) : s;
    std::cout << result << std::endl;
    return 0;
}
