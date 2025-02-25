#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
    char* text;
    size_t size;
    size_t real_size;
} string;

typedef struct student {
    int grade_num;
    char grade_c;
    string surname;
    string name;
    string date;
} student;


int cmp_students(const void* a, const void* b) {
    const student* s1 = (const student*)a;
    const student* s2 = (const student*)b;

    if (s1->grade_num < s2->grade_num)
        return -1;
    else if (s1->grade_num > s2->grade_num)
        return 1;
    if (s1->grade_c < s2->grade_c)
        return -1;
    else if (s1->grade_c > s2->grade_c)
        return 1;

    return strcmp(s1->surname.text, s2->surname.text);
}

void q_sort(student* students, int begin, int end) {
    if (begin >= end)
        return;

    int l = begin, r = end;
    student pivot = students[begin + (end - begin) / 2];

    while (l <= r) {
        while (cmp_students(&students[l], &pivot) < 0)
            l++;
        while (cmp_students(&students[r], &pivot) > 0)
            r--;
        if (l <= r) {
            student tmp = students[l];
            students[l] = students[r];
            students[r] = tmp;
            l++;
            r--;
        }
    }

    q_sort(students, begin, r);
    q_sort(students, l, end);
}

void get_line(string* s) {
    s->size = 0;
    s->real_size = 0;
    s->text = NULL;

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (s->size + 1 > s->real_size) {
            s->real_size = s->real_size ? s->real_size * 2 : 1;
            s->text = (char*) realloc(s->text, s->real_size);
        }
        s->text[s->size++] = (char)c;
    }
    if (s->text) {
        if (s->size + 1 > s->real_size) {
            s->real_size = s->real_size ? s->real_size * 2 : 1;
            s->text = (char*) realloc(s->text, s->real_size);
        }
        s->text[s->size] = '\0';
    }
}

void print_string(const string* s) {
    printf("%s ", s->text);
}

void print_student(const student* st) {
    printf("%d%c ", st->grade_num, st->grade_c);
    print_string(&st->surname);
    print_string(&st->name);
    print_string(&st->date);
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();

    student* students = (student*) malloc(n * sizeof(student));

    for (int i = 0; i < n; i++) {
        get_line(&students[i].surname);
        get_line(&students[i].name);

        string class_line;
        get_line(&class_line);
        sscanf(class_line.text, "%d%c", &students[i].grade_num, &students[i].grade_c);
        free(class_line.text);

        get_line(&students[i].date);
    }

    q_sort(students, 0, n - 1);

    for (int i = 0; i < n; i++) {
        print_student(&students[i]);
    }

    for (int i = 0; i < n; i++) {
        free(students[i].surname.text);
        free(students[i].name.text);
        free(students[i].date.text);
    }
    free(students);

    return 0;
}
