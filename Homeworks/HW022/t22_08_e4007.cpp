#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>


using namespace std;



std::unordered_map<int, std::vector<int>> graph;



std::vector<int> right_reorder(const std::vector<int>& vec){
    return {vec[3], vec[0], vec[1], vec[2]};
}

std::vector<int> left_reorder(const std::vector<int>& vec){
    return {vec[1], vec[2], vec[3], vec[0]};
}

std::vector<int> plus_1(const std::vector<int>& vec){
    return {vec[0]+1, vec[1], vec[2], vec[3]};
}

std::vector<int> minus_1(const std::vector<int>& vec){
    return {vec[0], vec[1], vec[2], vec[3]-1};
}

std::vector<int> int_to_vec(int num){
    return {(num / 1000) % 10, (num/100) % 10,(num /10)%10 ,num % 10};
}

int vec_to_int(std::vector<int> vec){
    return vec[0]*1000 + vec[1]*100 + vec[2]*10 + vec[3];
}

void generate(){
    for (int i = 1111; i <= 9999; i++ ){
        auto curr = int_to_vec(i);
        graph[i].push_back(vec_to_int(right_reorder(curr)));
        graph[i].push_back(vec_to_int(left_reorder(curr)));
        if (curr[0] != 9)
            graph[i].push_back(vec_to_int(plus_1(curr)));
        if (curr[0] != 1)
            graph[i].push_back(vec_to_int(minus_1(curr)));
    }

}

void BFS(int start, int end){
    unordered_map<int, int> way;
    std::queue<int> q;
    q.push(start);
    way[start] = -1;

    while (!q.empty()){
        int curr = q.front(); q.pop();
        if (curr == end)
        for (auto neighbour: graph[curr]){
            if (way.find(neighbour) == way.end()){
                way[neighbour] = curr;
                q.push(neighbour);
            }
        }
    }

    std::vector<int> result;
    std::stack<int> st;
    int curr = end;
    while(curr != -1){
        st.push(curr);
        curr = way[curr];

    }

    while(!st.empty()){
        std::cout << st.top() << std::endl;
        st.pop();
    }



}


int main(){
    int start, finish;
    cin >> start >> finish;
    generate();
    BFS(start, finish);

}