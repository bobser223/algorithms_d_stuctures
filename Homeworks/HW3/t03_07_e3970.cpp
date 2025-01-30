//
// Created by Volodymyr Avvakumov on 28.01.2025.
//
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::vector;



int bs_leftmost(const vector<int>& all_creatures, int target){
    int left = 0;
    int right = all_creatures.size();

    while (left < right){
        int m = left + (right - left) / 2;

        if (all_creatures[m] < target){
            left = m + 1;
        } else {
            right = m;
        }
    }
    return left;
}

int bs_rightmost(const vector<int>& all_creatures, int target){
    int left = 0;
    int right = all_creatures.size();

    while (left < right){
        int m = left + (right - left) / 2;

        if (all_creatures[m] <= target){
            left = m + 1;
        } else {
            right = m;
        }
    }
    return left - 1;
}



void find_creatures_count(const vector<int>& all_creatures, const vector<int>& needed_creatures){
    for (int target: needed_creatures){
        int left = bs_leftmost(all_creatures, target);
        if (left == all_creatures.size() || all_creatures[left] != target){
            printf("%d\n", 0);
            continue;
        }
        int right = bs_rightmost(all_creatures, target);
        if (left == -1 || all_creatures[left] != target){
            printf("%d\n", 0);
            continue;
        }

        printf("%d\n", right - left + 1);

    }



}









int main(){
    int first_loop;
    vector<int> all_creatures;
    int second_loop;
    vector<int> needed_creatures;

    int buffer;

    cin >> first_loop;

    for (int i = 0; i < first_loop; i++){
        cin >> buffer;
        all_creatures.push_back(buffer);
    }

    cin >> second_loop;

    for (int i = 0; i < second_loop; i++){
        cin >> buffer;
        needed_creatures.push_back(buffer);
    }


    find_creatures_count(all_creatures, needed_creatures);
}