#include <vector>
#include <iostream>
using namespace std;

struct vertex{
    int input;
    int output;
    vertex(int _input, int _output): input(_input), output(_output) {}
    vertex(): input(0), output(0) {}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, b1, b2;
    cin>>n>>m;
    vector<vertex> vec(n);
    vec.resize(n);

    for (int i = 0; i < m; i++){
        cin >> b1 >> b2;
        vec[b1-1].output++;
        vec[b2-1].input++;
    }

    for(int i = 0; i < n; i++){
        cout << vec[i].input << " " << vec[i].output << endl;
    }



}
