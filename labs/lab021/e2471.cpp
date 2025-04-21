#include <iostream>
#include <vector>


int main(){
    int n, buff;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cin >> buff;
            if (j > i) {
                if (buff == 1) {
                    std::cout << (i + 1) << " " << (j + 1) << std::endl;
                }
            }
        }
    }

}