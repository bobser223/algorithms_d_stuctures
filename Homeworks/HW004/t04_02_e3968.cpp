#include <cmath>
#include <iostream>

double f(double m) {
    return m*m + sqrt(m);
}

double solve(int C){
    double eps = 0.0000006;

    double l = 0;
    double r = f(1000);
    while (abs(r - l) > eps){
        double m = l + (r - l) / 2.0;
        std::cout << m << std::endl;
        if (f(m) < C){
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}


int main(){
    int C;
    std::cin >> C;
    std::cout << solve(C) << std::endl;

}