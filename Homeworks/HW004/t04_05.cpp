#include <iostream>
#include <cmath>


double f(double x){
    return pow(x, 3) + 4*pow(x, 2) + x;
}

double solve(){
    double l, r;
    l = 0;
    r = 2;
    double m = l + (r - l) / 2;
    while (fabs(f(m) - 6) > 0.0000001){

        if (f(m) < 6)
            l = m;
        else
            r = m;
        m = l + (r - l) / 2;
    }

    return m;
}



int main(){
    std::cout << solve() << std::endl; // 1
    std::cout << f(solve()) - 6 << std::endl; // 0

}

