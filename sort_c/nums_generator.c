#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 // 100 мільйонів

int generate(int count) {
    FILE *fp = fopen("random_numbers.txt", "w");
    if (fp == NULL) {
        perror("Помилка відкриття файлу для запису");
        return EXIT_FAILURE;
    }

    // Ініціалізуємо генератор випадкових чисел
    srand((unsigned)time(NULL));

    // Записуємо NUM_COUNT випадкових чисел, кожне в окремому рядку
    for (size_t i = 0; i < count; i++) {
        fprintf(fp, "%d\n", rand());
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
