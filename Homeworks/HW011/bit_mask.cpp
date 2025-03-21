#include <iostream>


class bit_mask{
private:
    int num;
    int size;
public:
    explicit bit_mask(int arr_size) : num(0), size(arr_size) {}

    ~bit_mask() = default;

    void set_one(int position){
        num = num | (1 << (size - position));
    }

    void change_bit(int position){
        num = num ^ (1 << (size - position));
    }

    void set_zero(int position){
        num = num & ~(1 << (size - position));
    }

    void print() const {
        for (int i = size - 1; i >= 0; --i) {
            std::cout << ((num >> i) & 1);
        }
        std::cout << std::endl;
    }



};



int main() {
    bit_mask bm(8);  // Create an 8-bit mask.

    // Initially, all bits are 0.
    bm.print();  // Output: 00000000

    // Set the 3rd bit (from the left) to 1.
    bm.set_one(3);
    bm.print();  // Example output: 00100000

    // Toggle the 3rd bit: it becomes 0.
    bm.change_bit(3);
    bm.print();  // Output: 00000000

    // Set the 5th bit to 1, then set it back to 0.
    bm.set_one(5);
    bm.print();  // Example output: 00001000
    bm.set_zero(5);
    bm.print();  // Output: 00000000

    return 0;
}