#include <iostream>
#include <cmath>


double f(double x){
    return sin(x)/x;
}

double solve(){
    double l, r;
    l = 1.6;
    r = 3;
    double m = l + (r - l) / 2;
    while ((f(m) - 0.3) > 0.0000001){

        if (f(m) < 0.3333)
            l = m;
        else
            r = m;
        m = l + (r - l) / 2;
    }

    return l;
}



int main(){
    std::cout << solve() << std::endl;
    std::cout << f(solve()) - 0.3 << std::endl;

}
