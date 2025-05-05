#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <string>

using boost::multiprecision::cpp_int;

int main() {
    // 1) Declare big integers
    cpp_int a = 1;                // from integer literal
    cpp_int b("123456789012345678901234567890"); // from decimal string


    // 2) Arithmetic works as usual
    cpp_int sum = a + b;
    cpp_int prod = b * 42;
    cpp_int pow2 = cpp_int(1) << 200;  // 2^200 via bit‐shift

    // 3) Conversions
    std::string s = sum.convert_to<std::string>();
    long long small = (long long)(a + 5); // if it fits in built-in type

    // 4) I/O streaming
    std::cout << "b = " << b << "\n"
              << "sum = " << sum << "\n"
              << "2^200 = " << pow2 << "\n";

    // 5) Example: compute factorial(50)
    cpp_int fact = 1;
    for (int i = 1; i <= 50; ++i) fact *= i;
    std::cout << "50! = " << fact << "\n";

    return 0;
}
