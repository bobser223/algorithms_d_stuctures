#include <iostream>
#include <vector>





int main(){
    int n, m, buff_1, buff_2;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        std::cin >> buff_1 >> buff_2;

        matrix[buff_1-1][buff_2-1] = 1;
    }


    for (auto& row : matrix){
        for (int value: row){
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }







}
