#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using ll = long long;
const ll INF = (1LL << 60);
const int MAXN = 100000;

template<typename T, typename BinOp>
class SegmentTree {
    int n;
    vector<T> t;
    BinOp op;
    T id;
public:
    SegmentTree(const vector<T>& a, BinOp _op, T _id)
            : op(_op), id(_id)
    {
        int sz = a.size();
        n = 1;
        while (n < sz) n <<= 1;
        t.assign(2 * n, id);
        for (int i = 0; i < sz; ++i)
            t[n + i] = a[i];
        for (int v = n - 1; v > 0; --v)
            t[v] = op(t[v << 1], t[v << 1 | 1]);
    }

    void update(int pos, const T& val) {
        int v = pos + n;
        t[v] = val;
        for (v >>= 1; v > 0; v >>= 1)
            t[v] = op(t[v << 1], t[v << 1 | 1]);
    }

    T query(int l, int r) const {
        T resL = id, resR = id;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)    resL = op(resL, t[l++]);
            if (!(r & 1)) resR = op(t[r--], resR);
        }
        return op(resL, resR);
    }
};

inline ll initial_value(int n) {
    return (1LL * n * n) % 12345
           + (1LL * n * n * n) % 23456;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<ll,ll>> base(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        ll v = initial_value(i + 1);
        base[i] = {v, v};
    }

    auto comb = [](const pair<ll,ll>& a, const pair<ll,ll>& b) {
        return make_pair(min(a.first,  b.first),
                         max(a.second, b.second));
    };
    SegmentTree<pair<ll,ll>, decltype(comb)>
            st(base, comb, {INF, -INF});

    int k;
    cin >> k;
    while (k--) {
        ll x, y;
        cin >> x >> y;
        if (x > 0) {
            int l = int(x) - 1;
            int r = int(y) - 1;
            auto res = st.query(l, r);
            cout << (res.second - res.first) << '\n';
        } else {
            int pos = int(-x) - 1;
            st.update(pos, {y, y});
        }
    }
    return 0;
}
