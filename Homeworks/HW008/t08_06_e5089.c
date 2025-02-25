#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct string{
    char* text;
    size_t size;
    size_t real_size;
} string;


void get_line(string* s){

    s->size = 0;
    s->real_size = 0;
    s->text = NULL;

    char c;

    while((c = getchar()) != '\n' && c != EOF){
        if (s->size + 1 > s->real_size ){
            s->real_size = s->real_size ? s->real_size * 2 : 1;
            s->text = (char*)realloc(s->text, s-> real_size);
        }
        s->text[s->size++] = c;
    }
}

void print_string(const string* s){
    for (size_t i = 0; i < s->size; i++){
        printf("%c", s->text[i]);
    }
    printf("\n");
}

int is_greater(const string* a, const string* b){
    //is a > b
    int cmp = strcmp(a->text, b->text);
    return cmp > 0;
}

void insertion_sort(string* str, int size){
    for (int i = 1; i < size ; i++){
        string curr_s = str[i];
        int pos = i;


        while(pos > 0){
            if (is_greater(&str[pos -1], &curr_s))
                str[pos] = str[pos-1];
            else{
                break;
            }
            pos --;
        }
        str[pos] = curr_s;

    }

}



int main(){
    int n;
    scanf("%d", &n);
    getchar(); // '\n'

    string* russ_lang = (string*)malloc(n*sizeof(string));
    for (int i = 0; i < n; i++){
        get_line(&russ_lang[i]);
    }


    insertion_sort(russ_lang, n);

    for (int i = 0; i < n; i++){
        print_string(&russ_lang[i]);
    }


    for (int i = 0; i < n; i++){
        free(russ_lang[i].text);
    }


    free(russ_lang);
}



