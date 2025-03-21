#include<iostream>
#include <set>
#include <vector>

using namespace std;

struct barrel{
  int left;
  int right;
  int weight;

  explicit barrel(int w){
      weight = w;
      left = 0;
      right = 0;
  }

  barrel(const barrel& other){
      left = other.left;
      right = other.right;
      weight = other.weight;
  }
};

int n, m;
set<int> s;
vector<int> barrels;
vector<int> plates;

void solution(int i, barrel b){
    if (i == m){
        if (b.right - b.left == 0){
            s.insert(b.weight + b.right*2);

        }
        return;
    }

    barrel new_barrel = b;
    solution(i+1, b);
    b.left += plates[i];
    solution(i+1, b);
    b.left -= plates[i];
    b.right += plates[i];
    solution(i+1, b);

}






int main(){


    cin >> n >> m;
    barrels.resize(n);
    plates.resize(m);
    for (int i = 0; i < n; i++){
        cin >> barrels[i];
    }
    for (int i = 0; i < m; i++){
        cin >> plates[i];
    }

    for(int barr_weight : barrels){
        barrel barr(barr_weight);
        solution(0, barr);
    }

    for(const auto& el:s){
        cout << el << endl;
    }

}
