#include <iostream>
#include <vector>





int main(){
    int n, buff_1, buff_2;
    std::cin >> n;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        for (int t = 0; t < k; ++t) {
            int v;
            std::cin >> v;
            // ставимо 1 у матриці: з i → (v-1)
            matrix[i][v-1] = 1;
        }
    }


    for (auto& row : matrix){
        for (int value: row){
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }







}
