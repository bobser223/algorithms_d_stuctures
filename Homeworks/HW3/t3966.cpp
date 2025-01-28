#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::vector;



int bs(const vector<int>& vec, int target){
    int left = 0;
    int right = vec.size() - 1;

    while(left <= right){
        int m = left + (right - left) / 2;

        if (vec[m] == target){
            return 1;
        }

        if (vec[m] < target){
            left = m + 1;
        } else{
            right = m - 1;
        }
    }

    return  0;
}



void find_butterflies(const vector<int>& butterflies, const vector<int>& targets){

    for (int i = 0; i < targets.size(); i++){
        if (bs(butterflies, targets[i])){
            printf("YES\n");
        } else {
            printf("NO\n");
        }

    }



}




int main(){
    int first_loop;
    vector<int> all_butterflies;
    int second_loop;
    vector<int> needed_butterflies;

    int buffer;

    cin >> first_loop;

    for (int i = 0; i < first_loop; i++){
        cin >> buffer;
        all_butterflies.push_back(buffer);
    }

    cin >> second_loop;

    for (int i = 0; i < second_loop; i++){
        cin >> buffer;
        needed_butterflies.push_back(buffer);
    }


    find_butterflies(all_butterflies, needed_butterflies);
}