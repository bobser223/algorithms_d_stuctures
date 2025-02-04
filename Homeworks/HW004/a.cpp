#include <iostream>
#include <vector>

using namespace std;

bool binarySearch(vector<int> arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return true;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

void answer(int n, vector<int> v1, int m, vector<int> v2) {
    for (int i = 0; i < m; i++) {
        if (binarySearch(v1, v2[i]))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> collection(n);
    for (int i = 0; i < n; i++)
        cin >> collection[i];

    int m;
    cin >> m;
    vector<int> collection_question(m);
    for (int i = 0; i < m; i++)
        cin >> collection_question[i];

    answer(n, collection, m, collection_question);
}