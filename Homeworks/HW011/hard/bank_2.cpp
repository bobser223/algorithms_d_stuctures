#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> salary, bills;
vector<bool> used;


bool assignSalary(int person, int start, int currentSum) {
    if (currentSum == salary[person]) {
        if (person == n - 1)
            return true;
        return assignSalary(person + 1, 0, 0);
    }
    for (int i = start; i < m; i++) {
        if (!used[i] && currentSum + bills[i] <= salary[person]) {
            used[i] = true;
            if (assignSalary(person, i + 1, currentSum + bills[i]))
                return true;
            used[i] = false;
        }
    }
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
    used.assign(m, false);

    bool ok = assignSalary(0, 0, 0);
    cout << (ok ? "YES" : "NO") << endl;

    return 0;
}
