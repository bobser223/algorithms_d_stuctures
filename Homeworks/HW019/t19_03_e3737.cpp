#include <vector>
#include <iostream>




int main(){
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for(int i = 0; i < n; i++){
        std::cin >> vec[i];
//        std::cout << vec[i] << " ";
    }

    int i = 0;

    while (2*i + 1 < n){
        if (vec[i] > vec[2*i + 1]){
            std::cout << "NO\n";
            return 0;
        }
        i++;
    }

    i = 0;
    while (2*i + 2 < n){
        if (vec[i] > vec[2*i + 2]){
            std::cout << "NO\n";
            return 0;
        }
        i++;
    }



    std::cout << "YES\n";
}
