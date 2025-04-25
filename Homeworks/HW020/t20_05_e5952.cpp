#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

class SegmentTree {
private:
    ll size;
    vector<ll> tree, lazy;

    void push(ll node, ll l, ll r) {
        if (lazy[node] != 0) {
            tree[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(ll node, ll l, ll r, ll ql, ll qr, ll val) {
        push(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        update_range(2 * node, l, mid, ql, qr, val);
        update_range(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    ll query_range(ll node, ll l, ll r, ll ql, ll qr) {
        push(node, l, r);
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        ll mid = (l + r) / 2;
        return query_range(2 * node, l, mid, ql, qr) +
               query_range(2 * node + 1, mid + 1, r, ql, qr);
    }

public:
    SegmentTree(ll n) {
        size = n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void update(ll l, ll r, ll val) {
        update_range(1, 0, size - 1, l, r, val);
    }

    ll query(ll l, ll r) {
        return query_range(1, 0, size - 1, l, r);
    }
};

int main() {

    ll q, L, R, p;
    cin >> q >> L >> R >> p;

    SegmentTree seg(256);

    for (ll i = 0; i < q; ++i) {
        ll l = min(L, R);
        ll r = max(L, R);

        seg.update(l, r, 1);

        if (i + 1 == q) break;

        ll sum = seg.query(l, r);
        L = sum % p;
        R = 255 - (sum % p);
    }

    cout << seg.query(0, 255) << endl;
    return 0;
}
