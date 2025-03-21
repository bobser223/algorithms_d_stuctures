#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> salary, bills;
vector<int> cand[1001];
vector<vector<int>> dp;
vector<int> sumMask;


bool canPay(int idx, int mask) {
    if(idx == n)
        return true;
    if(dp[idx][mask] != -1)
        return dp[idx][mask] == 1;

    int target = salary[idx];
    for (int sub : cand[target]) {
        if ((mask & sub) == sub) {
            if (canPay(idx + 1, mask ^ sub)) {
                dp[idx][mask] = 1;
                return true;
            }
        }
    }
    dp[idx][mask] = 0;
    return false;
}

int main(){

    cin >> n >> m;
    salary.resize(n);
    bills.resize(m);
    for (int i = 0; i < n; i++){
        cin >> salary[i];
    }
    for (int j = 0; j < m; j++){
        cin >> bills[j];
    }


    sort(salary.rbegin(), salary.rend());

    int totalSub = 1 << m;
    sumMask.resize(totalSub, 0);
    for (int sub = 0; sub < totalSub; sub++) {
        int s = 0;
        for (int j = 0; j < m; j++) {
            if (sub & (1 << j))
                s += bills[j];
        }
        sumMask[sub] = s;
        if(s <= 1000)
            cand[s].push_back(sub);
    }
    dp.assign(n + 1, vector<int>(totalSub, -1));

    bool ok = canPay(0, totalSub - 1);
    if (ok){
        cout << "YES";
    } else {
        cout << "NO";
    };


    return 0;
}