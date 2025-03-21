#include <iostream>
#include <stack>
#include <string>
using namespace std;


string to_infix(const string& str) {
    stack<string> st;
    for (int i = (int)str.size() - 1; i >= 0; --i) {
        char c = str[i];
        if (c=='+'||c=='-'||c=='*'||c=='/') {
            if (st.size()<2) return "";
            string a = st.top(); st.pop();
            string b = st.top(); st.pop();
            st.push(a + c + b);
        } else {
            st.push(string(1,c));
        }
    }
    return st.empty() ? "" : st.top();
}



int main(){
    string str;
    cin >> str;
    cout << to_infix(str) << endl;
}
