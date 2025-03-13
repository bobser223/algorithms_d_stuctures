#include <iostream>
#include <algorithm>


#define NUSHA 0
#define BARASH 1


using namespace std;

const int MAX_N = 14;
const int MAX_POSSIBLE_WEIGHT = 702; // Найбільше, що може назбирати Нюша (7 печив по 100 кожне = 700).
int total_cookies; // кількість печева загалом
int n;
int cookies[MAX_N];
int* mask_sum;





class DP{
private:
    int* results_table;
    int size;

public:
    DP(int total_c,int max_possible_weight){
        init(total_c, max_possible_weight);
    }

    DP()= default;

    ~DP(){
        delete[] results_table;
    }

    void init(int total_c,int max_possible_weight){
        size = (1<<total_c) * 2 * 2 * max_possible_weight;
        results_table = new int[size];

        for (int i = 0; i < size; i++){
            results_table[i] = -1;  // -1 значить що ще не порахували
        }
    }

    static int find_index(int mask, int move, int first, int pigs_count){
        return (((mask*2 + move) * 2 + first) * MAX_POSSIBLE_WEIGHT) + pigs_count;
    }

    int get_result(int mask, int move, int first, int pigs_count){
        return results_table[find_index(mask, move, first, pigs_count)];
    }

    void add_result(int mask, int move, int first, int pigs_count, int value){
        results_table[find_index(mask, move, first, pigs_count)] = value;
    }

};

bool is_used(int mask, int i){
    if (mask & (1 << i)) // чи на i-й позиції одиниця
        return true;
    return false;
}


DP dp;

int foo(int mask, int move, int first, int pigs_count){

    if (__builtin_popcount(mask) == total_cookies) { // mask is full 11...11
        return pigs_count;
    }


    if (dp.get_result(mask, move, first, pigs_count) != -1)
        return dp.get_result(mask, move, first, pigs_count);

    // 0 - husha
    // 1 - barash
    int current_player = (move == 0 ? first : 1 - first);

    int best = (current_player == 0 ? -10000 : 10000);

    for (int i = 0; i < total_cookies; i++){
        if (!is_used(mask, i)){

            int new_mask = mask | (1 << i); // добавляємо одиницю на іту позицію

            // Якщо ходить Нюша, додаємо вагу цього печива в pigs_count,
            // якщо ходить Бараш, pigs_count не змінюється.
            int new_pigs_count = pigs_count + (current_player == 0 ? cookies[i] : 0);

            int result;

            if (move == 0) {
                result = foo(new_mask, 1, first, new_pigs_count);
            } else {
                int sheep_and_pig_sum = mask_sum[new_mask];
                int sheep_sum = sheep_and_pig_sum - new_pigs_count;


                int new_first;

                if (new_pigs_count < sheep_sum){
                    new_first = NUSHA; // HUSHA
                } else if (new_pigs_count > sheep_sum){
                    new_first = BARASH;
                } else { // new_pigs_count == sheep_sum
                    new_first = first;
                }

                result = foo(new_mask, 0, new_first, new_pigs_count);
            }


            if (current_player == 0){
                best = max(best, result);
            } else {
                best = min(best, result);
            }

        }


    }
    dp.add_result(mask, move, first, pigs_count, best);
    return best;

}



int main(){
    cin >> n;
    total_cookies = 2*n;
    for(int i = 0; i < total_cookies; i++){
        cin >> cookies[i];
    }

    int mask_count = (1 << total_cookies);
    mask_sum = new int[mask_count];
    for(int mask = 0; mask < mask_count; mask++){
        int sum = 0;
        for (int i = 0; i < total_cookies; i++){
            if (is_used(mask, i)){
                sum += cookies[i];
            }
        }
        mask_sum[mask] = sum;
    }

    dp.init(total_cookies, MAX_POSSIBLE_WEIGHT);


    cout << foo(0, 0, 0, 0) << endl;


    delete[] mask_sum;
}