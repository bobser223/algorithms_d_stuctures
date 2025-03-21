#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 14; // У задачі 2n <= 14, тож 14 - це максимум загальної кількості печив.
int n;                       // n - це кількість печив для кожного гравця, тобто всього печив 2 * n
int total_cookies;            // total_cookies = 2 * n
int cookies[MAX_N];  // Маси (ваги) кожного з 2n печив

// Масив, у якому для кожної побітової маски зберігається сума ваг обраних печив.
// Розмір - 2^(total_cookies).
int *mask_sum = nullptr;

// Глобальна таблиця dp, де dp[mask][move][first][totalN] зберігає кінцеву вагу Нюші (0..700)
// для заданого стану. Замість 4-вимірного масиву реалізуємо один великий 1D-масив.
const int MAX_POSSIBLE_WEIGHT = 702; // Найбільше, що може назбирати Нюша (7 печив по 100 кожне = 700).
int dpSize = 0;        // загальна кількість можливих станів
short *dp = nullptr;   // масив для мемоізації

// Ініціалізуємо dp-таблицю значенням -1 (що означає "ще не обчислено").
void initDP() {
    dpSize = (1 << total_cookies) * 2 * 2 * MAX_POSSIBLE_WEIGHT;
    dp = new short[dpSize];
    for (int i = 0; i < dpSize; i++) {
        dp[i] = -1;
    }
}

// Функція обчислення індексу у великому 1D-масиві dp за (mask, move, first, pigs_count).
inline int stateIndex(int mask, int move, int first, int pigs_count) {
    // Розкладемо 4-вимірний індекс в один:
    return (((mask * 2 + move) * 2 + first) * MAX_POSSIBLE_WEIGHT) + pigs_count;
}

// Рекурсивна функція f: повертає максимально можливу кінцеву вагу Нюші.
// Параметри:
//   mask     – біти встановлені для вже вибраних печив
//   move     – 0 (перший хід) або 1 (другий хід)
//   first    – 0 (Нюша перша) або 1 (Бараш перший) у поточному раунді
//   pigs_count   – скільки ваги вже набрала Нюша
int f(int mask, int move, int first, int pigs_count) {
    // Якщо вже обрано всі печива (кількість встановлених бітів == total_cookies),
    // то це кінець гри, повертаємо вагу Нюші.
    if (__builtin_popcount(mask) == total_cookies) {
        return pigs_count;
    }

    // Перевіряємо, чи маємо результат цього стану в dp.
    int idx = stateIndex(mask, move, first, pigs_count);
    if (dp[idx] != -1) {
        return dp[idx];
    }

    // Визначаємо, хто зараз ходить:
    // якщо move == 0, це гравець 'first', якщо move == 1, навпаки.
    int current_player = (move == 0 ? first : 1 - first);

    // Залежно від того, хто ходить, ініціалізуємо "best":
    // - Якщо це Нюша (currentPlayer == 0), вона намагається МАКСИМІЗУВАТИ результат
    // - Якщо Бараш (currentPlayer == 1), він намагається МІНІМІЗУВАТИ результат
    int best = (current_player == 0) ? -10000 : 10000;

    // Перебираємо всі печива, які ще не вибрані (біт i в mask == 0).
    for (int i = 0; i < total_cookies; i++) {
        if (!(mask & (1 << i))) {
            // "Включаємо" i-те печиво в маску
            int newMask = mask | (1 << i);

            // Якщо ходить Нюша, додаємо вагу цього печива в pigs_count,
            // якщо ходить Бараш, pigs_count не змінюється.
            int add = (current_player == 0 ? cookies[i] : 0);
            int newTotalN = pigs_count + add;

            int res;
            if (move == 0) {
                // Якщо це перший хід у раунді, далі піде другий хід (move=1)
                res = f(newMask, 1, first, newTotalN);
            } else {
                // Якщо це другий хід, раунд завершився.
                // Підраховуємо сумарну вагу всіх вибраних печив:
                int rSum = mask_sum[newMask];
                int totalB = rSum - newTotalN; // Вага в Бараша

                // Визначаємо, хто буде ходити першим у наступному раунді
                int newFirst;
                if (newTotalN < totalB) {
                    newFirst = 0;  // У Нюші менше => Нюша ходитиме першою
                } else if (newTotalN > totalB) {
                    newFirst = 1;  // У Бараша менше => Бараш ходитиме першим
                } else {
                    newFirst = first; // Якщо рівність, порядок не змінюємо
                }
                // Наступний раунд починається з move=0.
                res = f(newMask, 0, newFirst, newTotalN);
            }

            // Оновлюємо "best" за принципом мінімаксу:
            if (current_player == 0) {
                // Нюша шукає максимум
                best = max(best, res);
            } else {
                // Бараш шукає мінімум
                best = min(best, res);
            }
        }
    }

    dp[idx] = (short)best;
    return best;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    total_cookies = 2 * n;

    // Зчитуємо ваги печив
    for (int i = 0; i < total_cookies; i++) {
        cin >> cookies[i];
    }

    // Попередньо для кожної possible mask рахуємо суму ваги
    int mask_count = (1 << total_cookies);
    mask_sum = new int[mask_count];
    for (int mask = 0; mask < mask_count; mask++) {
        int s = 0;
        for (int i = 0; i < total_cookies; i++) {
            if (mask & (1 << i)) {
                s += cookies[i];
            }
        }
        mask_sum[mask] = s;
    }

    // Ініціалізуємо dp-таблицю значенням -1
    initDP();

    // Стартовий стан гри:
    // mask=0 (печива не вибрані),
    // move=0 (перший хід у раунді),
    // first=0 (Нюша починає першою),
    // totalN=0 (Нюша ще не взяла жодного печива).
    int res = f(0, 0, 0, 0);

    // Виводимо результат
    cout << res << "\n";

    // Звільняємо пам'ять
    delete[] dp;
    delete[] mask_sum;
    return 0;
}
