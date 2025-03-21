#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool correct(const string& str) {
    stack<char> st;
    for (char ch : str) {
//        if (ch == ' ' || ch == '\t') continue;

        if (ch == '(' || ch == '[') {
            st.push(ch);
        }
        else if (ch == ')') {
            if (st.empty() || st.top() != '(') return false;
            st.pop();
        }
        else if (ch == ']') {
            if (st.empty() || st.top() != '[') return false;
            st.pop();
        }
        else {
            // Unexpected character: treat as invalid
//            return false;
        }
    }
    return st.empty();
}

int main() {
    int n;
    if (!(cin >> n)) return 0;         // Read number of test cases
    string buff;

    getline(cin, buff);

    while (n--) {
        getline(cin, buff);
        cout << (correct(buff) ? "Yes" : "No") << '\n';
    }
    return 0;
}