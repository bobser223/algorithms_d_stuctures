#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

int bit_count(int n){
    int count = 0;
    while (n) {
        count++;
        n >>= 1;
    }
    return count;
}

int find_max(const vector<int>& vec){
    int max_el = vec[0];
    for (int i = 1; i < vec.size(); i++){
        if (vec[i] > max_el)
            max_el = vec[i];
    }
    return max_el;
}

int  max_cyclic_shift(int n){
    vector<int> all_shifts;
    unsigned int curr_shift = n;
    unsigned int n_bit_size = bit_count(n);
//    std::bitset<32> bits4(n);
//    std::cout << "n: " << bits4 << std::endl;

    for (int i = 0; i < n_bit_size; i++) {
        unsigned buffer = curr_shift >> (n_bit_size - 1);

//        std::bitset<32> bits(buffer);
//        std::cout << "buffer = curr_shift >> (n_bit_size - 1): " << bits << std::endl;

        curr_shift = curr_shift << (sizeof(int)*8 + 1 - n_bit_size);
        curr_shift = curr_shift >> (sizeof(int)*8  - n_bit_size);

//        std::bitset<32> bits2(curr_shift);
//        std::cout << "curr_shift << 1: " << bits2 << std::endl;

        curr_shift = (buffer | curr_shift);

//        std::bitset<32> bits3(curr_shift);
//        std::cout << "(buffer | curr_shift): " << bits3 << std::endl;

        all_shifts.push_back(curr_shift);
    }

    return find_max(all_shifts);

}





int main(){
    int n;
    cin >> n;
    cout << max_cyclic_shift(n) << endl;
}
