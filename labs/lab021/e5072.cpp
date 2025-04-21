#include <iostream>
int main(){ int n, k, sum = 0; std::cin >> n; for (int i = 0; i < n*n; i++){ scanf("%d", &k); sum += k;}printf("%d\n", sum);}