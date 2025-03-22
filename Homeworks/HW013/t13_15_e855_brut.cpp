#include<stack>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

vector<string> correct_brackets;

const array<char,4> CHARS = {'(', '[', ')', ']'};

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


void gen(int n,const string& str){

    if (str.size() == n){
        if (correct(str)){
            correct_brackets.push_back(str);
        }
        return;
    }

    for (auto el: CHARS){
        string buff(str);
        buff += el;
        gen(n, buff);
    }


}


int main(){
    int n;
    cin >> n;
    gen(n, "");
    for (auto str: correct_brackets){
        cout << str << endl;
    }

}