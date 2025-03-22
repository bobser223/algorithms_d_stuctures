#include<stack>
#include <iostream>
#include <string>




using namespace std;

void is_correct(const string& str){
    stack<char> st;
    for (char ch: str){
        if (ch == ' ') continue;

        if (ch == '[' || ch == '(' || ch == '{') st.push(ch);
        else if (!st.empty()){
            if (ch == ')'){
                if (st.top() == '(') {
                    st.pop();
                    continue;
                } else {
                    printf("no");
                    return;
                }
            }

            if (ch == '}'){
                if (st.top() == '{'){
                    st.pop();
                    continue;
                } else {
                    printf("no");
                    return;
                }
            }

            if (ch == ']'){
                if (st.top() == '['){
                    st.pop();
                    continue;
                } else {
                    printf("no");
                    return;
                }
            }
        } else{
            printf("no");
            return;
        }

    }
    cout << (st.empty()? "yes": "no") << endl;
}



int main(){
    string str;
    getline(cin, str);
    is_correct(str);
}