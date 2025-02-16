#include <stdio.h>
#include <stdlib.h>

#define NUM_COUNT 1000000


// Краще перейменувати функцію, щоб уникнути можливих конфліктів
void read(int *arr, int count) {
    FILE *fp = fopen("random_numbers.txt", "r");
    if (fp == NULL) {
        perror("Помилка відкриття файлу для зчитування");
        return;  // Завершуємо функцію при помилці
    }

    if (arr == NULL) {
        perror("Помилка: переданий масив є NULL");
        fclose(fp);
        return;
    }

    // Зчитуємо числа з файлу в масив
    for (size_t i = 0; i < count; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "Помилка зчитування числа на позиції %zu\n", i);
            fclose(fp);
            return;  // Завершуємо функцію при помилці
        }
    }

    fclose(fp);
}
