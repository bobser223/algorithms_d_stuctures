#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    vector<int> inp, outp;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Vertex> vec(n);

    // Читаємо матрицю та формуємо списки inp/outp
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int buff;
            cin >> buff;
            if (buff) {
                vec[i].outp.push_back(j + 1);
                vec[j].inp.push_back(i + 1);
            }
        }
    }

    vector<int> sources, sinks;
    for(int i = 0; i < n; i++){
        if (vec[i].inp.empty())
            sources.push_back(i + 1);
        if (vec[i].outp.empty())
            sinks.push_back(i + 1);
    }

    cout << sources.size();
    for (int v : sources)
        cout << ' ' << v;
    cout << '\n';

    cout << sinks.size();
    for (int v : sinks)
        cout << ' ' << v;
    cout << '\n';

    return 0;
}
