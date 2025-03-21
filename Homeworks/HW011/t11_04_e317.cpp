#include <iostream>
#include <string>
#include <unordered_map>
#include <gmp.h>

class Number {
private:
    mpz_t num;
public:
    Number(const std::string &str) {
        mpz_init(num);
        mpz_set_str(num, str.c_str(), 10);
    }

    Number() {
        mpz_init(num);
    }

    Number(long long val) {
        mpz_init(num);
        mpz_set_si(num, val);
    }

    Number(const Number &other) {
        mpz_init_set(num, other.num);
    }

    ~Number(){
        mpz_clear(num);
    }

    Number& operator=(const Number &other) {
        if (this != &other) {
            mpz_set(num, other.num);
        }
        return *this;
    }

    Number operator+(const Number &other) const {
        Number result;
        mpz_add(result.num, this->num, other.num);
        return result;
    }
    Number operator+(long long val) const {
        Number tmp(val);
        return (*this + tmp);
    }

    Number operator-(const Number &other) const {
        Number result;
        mpz_sub(result.num, this->num, other.num);
        return result;
    }
    Number operator-(long long val) const {
        Number tmp(val);
        return (*this - tmp);
    }

    Number operator*(const Number &other) const {
        Number result;
        mpz_mul(result.num, this->num, other.num);
        return result;
    }
    Number operator*(long long val) const {
        Number tmp(val);
        return (*this * tmp);
    }

    Number mul_10exp(unsigned long exp) const {
        Number result;
        mpz_t factor;
        mpz_init(factor);
        mpz_ui_pow_ui(factor, 10, exp);
        mpz_mul(result.num, this->num, factor);
        mpz_clear(factor);
        return result;
    }

    std::string get_string() const {
        char *c_str = mpz_get_str(nullptr, 10, this->num);
        std::string res(c_str);
        void (*freefunc)(void *, size_t);
        mp_get_memory_functions(nullptr, nullptr, &freefunc);
        freefunc(c_str, std::strlen(c_str)+1);
        return res;
    }
};

struct pair_hash {
    std::size_t operator()(const std::pair<std::string, std::string> &p) const {
        return std::hash<std::string>{}(p.first)
               ^ (std::hash<std::string>{}(p.second) << 1);
    }
};

static std::unordered_map< std::pair<std::string,std::string>, std::string, pair_hash > memo;

std::string get_memo(const std::string &x, const std::string &y) {
    auto it = memo.find({x, y});
    if (it != memo.end()) {
        return it->second;
    }
    return "-1";
}

void set_memo(const std::string &x, const std::string &y, const std::string &value) {
    memo[{x, y}] = value;
}

std::string karatsuba(const std::string &X, const std::string &Y) {
    std::string cached = get_memo(X, Y);
    if (cached != "-1") {
        return cached;
    }

    if (X.size() <= 7 && Y.size() <= 7){
        Number _X(X);
        Number _Y(Y);
        set_memo(X, Y, (_X*_Y).get_string());
        return get_memo(X, Y);
    }

    if (X == "0" || Y == "0") {
        set_memo(X, Y, "0");
        return "0";
    }

    int n1 = (int)X.size();
    int n2 = (int)Y.size();
    int n  = (n1 > n2 ? n1 : n2);


    if (n <= 1) {
        Number a(X);
        Number b(Y);
        std::string ans = (a * b).get_string();
        set_memo(X, Y, ans);
        return ans;
    }


    std::string Xp = X;
    std::string Yp = Y;
    if (n1 < n) Xp = std::string(n-n1,'0') + Xp;
    if (n2 < n) Yp = std::string(n-n2,'0') + Yp;

    int m = n / 2;


    std::string A = Xp.substr(0, n - m);
    std::string B = Xp.substr(n - m);
    std::string C = Yp.substr(0, n - m);
    std::string D = Yp.substr(n - m);

    std::string AC = karatsuba(A, C);
    std::string BD = karatsuba(B, D);


    Number _A(A), _B(B), _C(C), _D(D);
    Number AB = _A + _B;
    Number CD = _C + _D;


    std::string middle = karatsuba(AB.get_string(), CD.get_string());
    Number _mid(middle), _AC(AC), _BD(BD);

    Number ADplusBC = _mid - _AC - _BD;

    Number part1 = _AC.mul_10exp(2*m);
    Number part2 = ADplusBC.mul_10exp(m);
    Number total = part1 + part2 + _BD;

    std::string result = total.get_string();
    set_memo(X, Y, result);
    return result;
}

int main(){
    std::string X, Y;
    std::cin >> X >> Y;

    if (X.empty() || Y.empty()) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::string s = karatsuba(X, Y);

    std::cout << s << std::endl;
    return 0;
}
