#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

struct robots_time{
    ll busy_time = 0;
    ll default_exe_time;

    bool operator>(const robots_time& other) const {
        return busy_time > other.busy_time;
    }
};

void find_execution_time(ll needed_items, ll amount_1, std::vector<ll>& A_robots_time, ll amount_2, std::vector<ll>& B_robots_time){
    priority_queue<robots_time, vector<robots_time>, greater<robots_time>> pqA; // пріоритетна черга для A
    priority_queue<robots_time, vector<robots_time>, greater<robots_time>> pqB; // пріоритетна черга для B
    /*
     * r_time - елемент пріоритетної черги
     * vector<r_time> - контейнер для пріорітетної черги
     * greater<r_time> - позначка щоб елементи сортувалися за зростанням (треба для пріоритетної черги)
     */


    for (ll robot_time : A_robots_time) // ініціалізуємо чергу для А роботів
        pqA.push({robot_time, robot_time});

    for (ll robot_time : B_robots_time) // ініціалізуємо чергу для B роботів
        pqB.push({robot_time, robot_time});


    vector<ll> times(needed_items, 0);
    /*
     * сюди будемо записувати почерзі час виконання роботи i-м роботом
     */


    for (int i = 0; i < needed_items; i++){ // жадібно виконуємо роботу для А роботів
        robots_time top = pqA.top();
        pqA.pop();

        times[i] = top.busy_time;
        /*
         * записуємо для кожного робота
         * скільки він в цілому попрацював
         */
        pqA.push({top.busy_time + top.default_exe_time, top.default_exe_time});
        /*
         * в чергу додаємо робота, що вже виконав роботу (до робочого часу додаємо час за який робот робить деталь)
         * Т.Я. це черга він автоматично потрапляє на своє місце
         */
    }

    ll max_time = 0;

    for (int i = needed_items - 1; i >= 0; i--){
        /*
         * Т.Я. в нашому times часи виконання роботи А
         * зберігаються від найшвидшого до найповільнішого, то тут
         *  підемо навпаки
         */

        robots_time top = pqB.top();
        pqB.pop();

        times[i] += top.busy_time;

        pqB.push({top.busy_time + top.default_exe_time, top.default_exe_time});

        /*
         * проробляємо теж саме що і з А
         */

        if (times[i] > max_time)
            max_time = times[i];
        /*
         * автоматично шукаємо коли найдовша деталь закінчить
         * опрацьовуватись (максимум зі списку, а отже і робочий час загалом)
         */


    }

    cout << max_time << endl;

}



int main(){
    ll items_needed;

    ll first_robots_amount;
    ll second_robots_amount;


    cin >> items_needed;


    cin >> first_robots_amount;
    std::vector<ll> first_robots_efficiency(first_robots_amount);

    for (ll i = 0; i < first_robots_amount; i++)
        cin >> first_robots_efficiency[i];


    cin >> second_robots_amount;
    std::vector<ll> second_robots_efficiency(second_robots_amount);


    for (ll i = 0; i < second_robots_amount; i++)
        cin >> second_robots_efficiency[i];

    find_execution_time(items_needed, first_robots_amount, first_robots_efficiency, second_robots_amount, second_robots_efficiency);
    return 0;
}