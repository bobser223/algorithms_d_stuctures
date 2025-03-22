#include<stack>
#include <iostream>
#include <string>

typedef long ll;


using namespace std;

string to_system(ll num, ll system){
    string str;
    stack <string> st;
    while (num > 0){
        ll rem = num % system;
        if (rem <= 9){
            st.push(to_string(rem));
        } else {
            st.push('[' + to_string(rem) + ']');
        }

        num /= system;


    }

    while (!st.empty()){
        str += st.top(); st.pop();
    }

    return str;
}




int main(){
    ll num, system;

    cin >> num;
    cin >> system;

    cout << to_system(num, system) << endl;


}