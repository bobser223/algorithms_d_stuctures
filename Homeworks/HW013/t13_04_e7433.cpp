#include<stack>
#include <iostream>
#include <string>


using namespace std;
bool isSmaller(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        return a.length() < b.length();
    return a < b;
}

std::string subtract(std::string a, std::string b) {
    std::string result;
    int carry = 0;

    while (b.length() < a.length())
        b = "0" + b;

    for (int i = a.length() - 1; i >= 0; --i) {
        int diff = (a[i] - '0') - (b[i] - '0') - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else carry = 0;
        result = char(diff + '0') + result;
    }

    result.erase(0, result.find_first_not_of('0'));
    return result.empty() ? "0" : result;
}

std::pair<std::string, std::string> divideWithRemainder(std::string a, std::string b) {
    if (b == "0") throw std::invalid_argument("Division by zero");

    std::string quotient;
    std::string remainder = "0";

    for (char digit : a) {
        remainder += digit;
        remainder.erase(0, remainder.find_first_not_of('0'));
        if (remainder.empty()) remainder = "0";

        int count = 0;
        while (!isSmaller(remainder, b)) {
            remainder = subtract(remainder, b);
            ++count;
        }
        quotient += char(count + '0');
    }

    quotient.erase(0, quotient.find_first_not_of('0'));
    if (quotient.empty()) quotient = "0";

    return {quotient, remainder};
}

string toSystem(string num, string system) {
    stack<string> st;
    while (num != "0") {
        auto [quotient, remainder] = divideWithRemainder(num, system);
        if (remainder.length() == 1 && remainder[0] <= '9')
            st.push(remainder);
        else
            st.push("[" + remainder + "]");
        num = quotient;
    }

    if (st.empty()) return "0";

    string result;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
}




int main(){
    string num, system;

    cin >> num;
    cin >> system;

    cout << toSystem(num, system) << endl;


}