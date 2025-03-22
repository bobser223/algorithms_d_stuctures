#include<stack>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
vector<string> correct_brackets;


void gen(int n,const stack<char>& st,const string& str){
    if (str.size() == n){
        if (st.empty()) correct_brackets.push_back(str);
        return;
    }

    if (st.empty()){
        // adding [
        stack<char> new_stack_1(st);
        string new_str_1(str);
        new_stack_1.push('[');
        new_str_1 += '[';
        gen(n, new_stack_1, new_str_1);

        //adding (
        stack<char> new_stack_2(st);
        string new_str_2(str);
        new_stack_2.push('(');
        new_str_2 += '(';
        gen(n, new_stack_2, new_str_2);

    } else if (st.top() == '('){
        // adding )
        stack<char> new_stack_1(st);
        new_stack_1.pop();
        string new_str_1(str);
        new_str_1 += ')';
        gen(n, new_stack_1, new_str_1);

        // adding [
        stack<char> new_stack_2(st);
        new_stack_2.push('[');
        string new_str_2(str);
        new_str_2 += '[';
        gen(n, new_stack_2, new_str_2);

        // adding (
        stack<char> new_stack_3(st);
        new_stack_3.push('(');
        string new_str_3(str);
        new_str_3 += '(';
        gen(n, new_stack_3, new_str_3);

    } else if (st.top() == '['){
        //adding ]
        stack<char> new_stack_1(st);
        new_stack_1.pop();
        string new_str_1(str);
        new_str_1 += ']';
        gen(n, new_stack_1, new_str_1);

        // adding (
        stack<char> new_stack_2(st);
        new_stack_2.push('(');
        string new_str_2(str);
        new_str_2 += '(';

        gen(n, new_stack_2, new_str_2);

        // adding [
        stack<char> new_stack_3(st);
        new_stack_3.push('[');
        string new_str_3(str);
        new_str_3 += '[';
        gen(n, new_stack_3, new_str_3);

    }

}


int main(){
    int n;
    cin >> n;
    gen(n,stack<char>{{'('}}, "(");
    gen(n, stack<char>{{'['}}, "[");
    for (auto str: correct_brackets){
        cout << str << endl;
    }

}