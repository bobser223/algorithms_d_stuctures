
#include <iostream>
#include <vector>
#include <fstream>


using std::cout;
using std::endl;
using std::cin;
using std::vector;

int count_ints(const vector<int>& nums, int min, int max){
    int result = 0;
    for(int i = 0; i < nums.size(); i++ )
        if (nums[i] >= min && nums[i] <= max)
            result++;

    return result;
}

void read_nums() {
    std::ifstream fin("input.txt");
    if (!fin.is_open()) {
        return;
    }

    int count, foo;
    int min, max;

    while (fin >> count) {
        vector<int> nums;

        if (count < 0) {
            break;
        }

        for (int i = 0; i < count; i++) {
            fin >> foo;
            nums.push_back(foo);
        }

        fin >> min;
        fin >> max;

        cout << count_ints(nums, min, max) << endl;
    }
}




int main(){
    read_nums();
}








