#include <iostream>
#include <cmath>

double f(double m){
    return m*m*m + m + 1;
}

double find(double a, double b, double c){
    double l = a;
    double r = b;

    double m = l + (r - l)/2;
    while(fabs(f(m) - c) > 0.00001){

        if (f(m) < c){
            l = m;
        } else{
            r = m;
        }
        m = l + (r - l)/2;
    }
    return r;
}


int main(){
    std::cout << find(0, 10, 5) << std::endl;
    std::cout << f(find(0, 10, 5)) << std::endl;

}