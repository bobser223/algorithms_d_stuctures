#include <iostream>
#include <vector>
#include <numeric>



using namespace std;

using ll = long long;

class SegmentTree{
private:
    vector<int> vec;
    int size;
public:
    explicit SegmentTree(const vector<int>& data){

        int k = data.size();
        int n = 1;

        while (n < k)
            n <<= 1;
        size = n;

        vec.resize(2*size, 0);

        for (int i = 0; i < k; i++)
            vec[n+i] = data[i];

        for (int i = n - 1; i > 0; i--){
            vec[i] = std::gcd(vec[2*i], vec[2*i + 1]);
        }
    }

    void gcd_range(int left, int right){
        int l = left+size;
        int r = right+size;
        ll gcd = 0;
        while(l <= r){
            if (l % 2 == 1)
                gcd = std::gcd(gcd, vec[l]);
            if (r%2 == 0)
                gcd = std::gcd(gcd, vec[r]);

            l = (l + 1) / 2;
            r = (r - 1) / 2;
        }
        cout << gcd << endl;
    }

    void update(int i, int value){
        int pos = i + size;
        vec[pos] = value;

        pos /= 2;
        while (pos > 0) {
            vec[pos] = std::gcd(vec[2*pos], vec[2*pos+1]);
            pos /= 2;
        }

    }
};


int main(){
    int n,m, q, l, r;
    cin >> n;
    vector<int> tmp(n);
    for(int i = 0; i < n; i++){
        cin >> tmp[i];
    }

    SegmentTree st(tmp);
    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> q >> l >> r;
        --l;
        if (q == 1) {
            --r;
            st.gcd_range(l, r);
        } else {
            st.update(l, r);
        }
    }


}