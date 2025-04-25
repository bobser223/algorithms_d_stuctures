#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;

template<typename T, typename BinaryOp>
class SegmentTree {
private:
    ll size;
    vector<T> vec;
    BinaryOp op;
    T identity;

public:
    SegmentTree(const vector<T>& data, BinaryOp operation, T identity)
            : op(operation), identity(identity)
    {
        ll k = data.size();
        ll n = 1;
        while (k > n) n <<= 1;
        size = n;

        vec.resize(2 * n, identity);

        for (ll i = 0; i < k; i++) {
            vec[n + i] = data[i];
        }
        for (ll i = n - 1; i > 0; i--) {
            vec[i] = op(vec[2 * i], vec[2 * i + 1]);
        }
    }

    ~SegmentTree() = default;

    void update(ll i, T value) {
        ll pos = i + size;
        vec[pos] = value;
        pos /= 2;
        while (pos > 0) {
            vec[pos] = op(vec[2 * pos], vec[2 * pos + 1]);
            pos /= 2;
        }
    }

    T query(ll left, ll right) {
        ll l = left + size;
        ll r = right + size;
        T result = identity;
        while (l <= r) {
            if (l % 2 == 1) result = op(result, vec[l]);
            if (r % 2 == 0) result = op(result, vec[r]);
            l = (l + 1) / 2;
            r = (r - 1) / 2;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, q, l, r;
    cin >> n;
    vector<ll> tmp(n);
    for (ll i = 0; i < n; i++) {
        cin >> tmp[i];
    }

    auto gcd_op = [](ll x, ll y) {
        return std::gcd(x, y);
    };
    auto lcm_op = [](ll x, ll y) {
        return std::lcm(x, y);
    };

    SegmentTree<ll, decltype(gcd_op)> st_gcd(tmp, gcd_op, 0LL);
    SegmentTree<ll, decltype(lcm_op)> st_lcm(tmp, lcm_op, 1LL);

    cin >> m;
    for (ll i = 0; i < m; i++) {
        cin >> q >> l >> r;
        --l;
        if (q == 1) {
            --r;
            ll g = st_gcd.query(l, r);
            ll L = st_lcm.query(l, r);
            if (g < L) {
                cout << "wins\n";
            } else if (g > L) {
                cout << "loser\n";
            } else {
                cout << "draw\n";
            }
        } else {
            st_gcd.update(l, r);
            st_lcm.update(l, r);
        }
    }

    return 0;
}
