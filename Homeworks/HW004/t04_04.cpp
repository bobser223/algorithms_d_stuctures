#include <iostream>
#include <cmath>


double f(double x){
    return sin(x)/x;
}

double solve(){
    double l = 1.6, r = 3;
    double m = l + (r - l) / 2;
    while (fabs(f(m) - 1.0/3) > 1e-7) {
        if (f(m) > 1.0/3)
            l = m;
        else
            r = m;
        m = l + (r - l) / 2;
    }
    return m;
}




int main(){
    std::cout << solve() << std::endl; // 2.27886
    std::cout << f(solve()) - 1/3.0 << std::endl; // -3.02505e-09 ~ 0

}


