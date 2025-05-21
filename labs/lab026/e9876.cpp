#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <iostream>
#include <stack>


using namespace std;

int str_siplity(string& s1, string& s2){
    int cnt = 0;
    for (int i = 0; i < s1.size(); i++){
        if (s1[i] == s2[i]) cnt ++;
    }
    return cnt;
}



void prim_algo(int n, int k, std::vector<std::string>& DNA){
    std::vector<bool> used(n, false);
    int used_count = 0;
    std::string& curr = DNA[0];

    while(used_count != n){
        std::stack<std::string> st;
        int max = INT32_MAX;
        int curr_i = 0;
        for (int i = 0; i < n;i++){
            if ()
        }


    }
}



int main(){
    int n, k;
    cin >> n >> k;

    std::vector<std::string> DNA(n);
    for (int i = 0; i < n; i++){
        cin >> DNA[i];
    }




}
