#include <cmath>
#include <iostream>

double f(double m) {
    return m*m + sqrt(m);
}

double solve(double C){
    double eps = 0.0000000006;

    double l = 0;
    double r = 10000000000.0;

    while (fabs(r - l) > eps){
        double m = l + (r - l) / 2.0;
        if (f(m) < C){
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}


int main(){
    double C;
    std::cin >> C;
    std::cout << solve(C) << std::endl;

}