#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
    string str;
    int priority;
};

string to_infix(const string& str) {
    char previous = '0';
    stack<Node> st;
    for (int i = (int)str.size() - 1; i >= 0; --i) {
        char c = str[i];
        if (isalpha(c)) {
            st.push({string(1, c), 3});
        } else {
            int curr_priority;

            if (c == '+' || c == '-'){
                curr_priority = 1;
            } else {
                curr_priority = 2;
            }

            Node left = st.top(); st.pop();
            Node right = st.top(); st.pop();

            string l_string = left.str;
            string r_string = right.str;

            if (left.priority < curr_priority){
                l_string = "(" + l_string + ")";
            }
            if (right.priority < curr_priority ||
            (right.priority == curr_priority && (c == '-' || c == '/'))){
                r_string = "(" + r_string + ")";
            }

            st.push({l_string + c + r_string, curr_priority});
        }

    }
    return st.empty() ? "" : st.top().str;
}



int main(){
    string str;
    cin >> str;
    cout << to_infix(str) << endl;
}
