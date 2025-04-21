#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>

class G{
private:
    std::vector<std::vector<int>> vec;

public:
    explicit G(int n): vec(n){}

    void add(int a, int b){
        vec[a-1].push_back(b);
        vec[b-1].push_back(a);
    }

    void vertex(int a){
        for (int vertex: vec[a-1])
            std::cout << vertex << " ";
        if (!vec[a-1].empty())
            std::cout << std::endl;
    }

};


int main(){
    int n, m, k, buff_1, buff_2;
    std::cin >> n;
    G g(n);
    std::cin >> m;
    for (int i = 0; i < m; i ++){
        std::cin >> k;
        if (k == 1){
            std::cin >> buff_1 >>  buff_2;
            g.add(buff_1, buff_2);
        } else {
            std::cin >> buff_1;
            g.vertex(buff_1);
        }
    }

}