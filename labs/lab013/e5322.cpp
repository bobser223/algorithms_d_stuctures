#include <iostream>
#include<stack>
#include <string>
#include <cmath>

using namespace  std;

int binaryToDecimal(const std::string& binary) {
    int decimal = 0;
    int length = binary.length();

    for (int i = 0; i < length; ++i) {
        if (binary[i] == '1') {
            decimal += pow(2, (length - i - 1));
        }
    }

    return decimal;
}

string to_base(int num, int base){
    string result;
    string digits = "0123456789ABCDEF";
    stack<char> st;
    while(num > 0){
        int rem = num % base;
        st.push(digits[rem]);
        num /= base;
    }

        while (!st.empty()) {
            result += st.top();
            st.pop();
        }

    return result;
}




int main(){
    string num;
    cin >> num;
    cout << to_base(binaryToDecimal(num), 16) << endl;
}