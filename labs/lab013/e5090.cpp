#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

typedef long long ll;

int main() {
    string line;
    getline(cin, line);

    stringstream ss(line);
    stack<ll> st;
    string token;

    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            ll b = st.top(); st.pop();
            ll a = st.top(); st.pop();
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else st.push(a / b);
        }
        else {
            st.push(stoll(token));
        }
    }

    cout << st.top() << '\n';
    return 0;
}
