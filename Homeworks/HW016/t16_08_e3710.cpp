#include <iostream>
#include <vector>
#include <set>

typedef long long ll;


using namespace std;

static const int Q = 127;
static const int MOD = 1000000007;

vector<ll> powers;
vector<ll> a_i;

struct Node {
    int id;
    int value;
    vector<Node*> kids;

    Node(int _id, int v): id(_id), value(v) {
        if (_id == -1) id = 0;
    }

    ~Node(){
        for (auto kid: kids){
            delete kid;
        }
    }
};

void fill_powers(int n){
    powers.resize(n);
    powers[0] = 1;
    for (int i = 1; i < n; i++){
        powers[i] = (powers[i-1] * Q) % MOD;
    }
}


std::pair<multiset<int>*, int> DFS(Node* node){
    multiset<int>* _set = new multiset<int>();
    int min_diff = INT_MAX;
    for (auto kid: node->kids){
        auto [kid_set, kid_diff] = DFS(kid);
        min_diff = min(min_diff, kid_diff);

        if (_set->size() < kid_set->size())
            swap(_set, kid_set);

        for (int x: *kid_set){
            auto it = _set->lower_bound(x);
            if (it != _set->end())
                min_diff = min(min_diff, abs(*it - x));
            if (it != _set->begin()) {
                auto pit = prev(it);
                min_diff = min(min_diff, abs(*pit - x));
            }
            _set->insert(x);
        }
        delete kid_set;
    }

    int x = node->value;
    auto it = _set->lower_bound(x);
    if (it != _set->end())
        min_diff = min(min_diff, abs(*it - x));
    if (it != _set->begin()) {
        auto pit = prev(it);
        min_diff = min(min_diff, abs(*pit - x));
    }
    _set->insert(x);

    if (!node->kids.empty())
        a_i[node->id] = min_diff;

    return {_set, min_diff};
}



int main(){
    //// input ///
    int n;
    cin >> n;

    vector<int> p(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> v[i];
    }

    vector<Node*> nodes;
    nodes.reserve(n);
    for (int i = 0; i < n; i++) {
        nodes.push_back(new Node(i, v[i]));
    }


    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        if (p[i] == -1) {
            root = nodes[i];
        } else {
            nodes[p[i]]->kids.push_back(nodes[i]);
        }
    }
    /// logic ////
    fill_powers(n);
    a_i.assign(n, 0);
    auto [foo, poo] = DFS(root);
    delete foo;

    ll result = 0;
    for(int i = 0; i < n; i++){
        if (!nodes[i]->kids.empty()){
            result = (result + a_i[i] + powers[i]) % MOD;
        }
    }

    cout << result << endl;

    delete root;
    return 0;
}