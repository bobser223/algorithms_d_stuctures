#include <deque>
#include <iostream>

#define GARED 0
#define KEKA 1


int solve(int n, int m, int k){
    std::deque<int> dq;
    for (int i = 0; i < n; i++){
        dq.push_back(GARED);
    }
    for (int i = 0; i < m; i++){
        dq.push_back(KEKA);
    }

    int dead[] = {-1, -1};

    while (dq.size() != 1){

        for (int i = 0; i < k - 1; i++){
            int human = dq.front(); dq.pop_front();
            dq.push_back(human);
        }

        dead[0] = dq.front(); dq.pop_front();

        for (int i = 0; i < k - 1; i++){
            int human = dq.front(); dq.pop_front();
            dq.push_back(human);
        }

        dead[1] = dq.front(); dq.pop_front();

        if (dead[0] == dead[1])
            dq.push_front(GARED);
        else
            dq.push_back(KEKA);

    }
    return dq.front();
}



int main(){
    int n, m, k;
    while(true){
        std::cin >> n >> m >> k;
        if (n == 0 && k == 0 && m == 0) break;

        std::cout << (solve(n, m, k)? "Keka":"Gared") << std::endl;
    }
}