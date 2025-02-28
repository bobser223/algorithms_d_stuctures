#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_arr(int* arr, size_t size) {
    for (size_t i = 0; i < size; i++)
        arr[i] = rand() % size;
}

//void print_arr(int* arr, size_t size) {
//    printf("[ ");
//    for (size_t i = 0; i < size; i++)
//        printf("%d, ", arr[i]);
//    printf("]\n");
//}

// Функція злиття двох відсортованих підмасивів arr[left..mid-1] та arr[mid..right-1]
// в допоміжний масив aux.
void b_merge(int* arr, int* aux, size_t left, size_t mid, size_t right) {
    size_t i = left, j = mid, k = left;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
        }
    }

    while (i < mid)
        aux[k++] = arr[i++];

    while (j < right)
        aux[k++] = arr[j++];
}

// Ітеративна (bottom-up) реалізація merge sort.
// На кожному кроці зливаємо сусідні підмасиви розміру 'width'.
void bottomUpMergeSort(int* arr, size_t n) {
    int* aux = (int*)malloc(n * sizeof(int));
    if (!aux) {
        perror("Помилка виділення пам'яті для допоміжного масиву");
        exit(EXIT_FAILURE);
    }

    // width - розмір підмасиву, який вже відсортовано
    for (size_t width = 1; width < n; width *= 2) {
        for (size_t i = 0; i < n; i += 2 * width) {
            size_t left = i;
            size_t mid = i + width;
            size_t right = i + 2 * width;

            if (mid > n)
                mid = n;
            if (right > n)
                right = n;

            b_merge(arr, aux, left, mid, right);
        }

        // Скопіювати допоміжний масив назад у основний
        for (size_t i = 0; i < n; i++)
            arr[i] = aux[i];
    }

    free(aux);
}

//int main() {
//    // Зауважте: для тестування з великими розмірами (наприклад, 1 мільярд)
//    // може знадобитися величезна кількість пам'яті, тому для тестів використовуйте менший розмір.
//    size_t arr_size = 1000000000; // приклад з 1 мільйоном елементів
//    int* arr_to_sort = (int*)calloc(arr_size, sizeof(int));
//    if (!arr_to_sort) {
//        perror("Помилка виділення пам'яті для масиву");
//        exit(EXIT_FAILURE);
//    }
//
//    fill_arr(arr_to_sort, arr_size);
//    // print_arr(arr_to_sort, arr_size); // Для невеликих масивів
//
//    clock_t start = clock();
//    bottomUpMergeSort(arr_to_sort, arr_size);
//    clock_t end = clock();
//
//    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
//    printf("Сортування зайняло %f секунд.\n", time_taken);
//
//    // print_arr(arr_to_sort, arr_size); // Перевірка результату
//
//    free(arr_to_sort);
//    return 0;
//}
