
#include <iostream>
#include <string>
#include <limits>
#include <cstdio>
#include <cstring>

#define cast_type unsigned char

struct swear_word{
    int count;
    std::string word;

};

struct waiting_list{
    // those S words hwo waits for curr char => this struct position in future arr
    int* swear_words_numbers;
    int count;
};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);


    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    auto swear_words = new swear_word[n];
    for (int i = 0; i < n; i++){
        getline(std::cin, swear_words[i].word);
        swear_words[i].count = 0;
    }


    std::string text;
    getline(std::cin, text);


    waiting_list waiting[128];

    for(int i = 0; i < 128; i++){
        waiting[i].swear_words_numbers = new int[n];
        waiting[i].count = 0;
    }

    for (int word_position = 0; word_position < n; word_position++){
        cast_type first_words_symbol = (cast_type)swear_words[word_position].word[0];
        waiting[first_words_symbol].swear_words_numbers[waiting[first_words_symbol].count++] = word_position;
    }


    for (int i = 0; i < text.size(); i++){
        cast_type curr_char_num = (cast_type)text[i];

        int waiting_count  = waiting[curr_char_num].count;
        waiting[curr_char_num].count = 0;

        for (int j = 0; j < waiting_count; j++){
            int waiting_index = waiting[curr_char_num].swear_words_numbers[j];

            swear_words[waiting_index].count ++;

            if (swear_words[waiting_index].word.size() == swear_words[waiting_index].count){
                printf("YES %d", i+1);

                for(int itr = 0; itr < 128; itr++){
                    delete[] waiting[itr].swear_words_numbers;
                }

                delete[] swear_words;
                return 0;
            }

            cast_type next_char = (cast_type)swear_words[waiting_index].word[swear_words[waiting_index].count];
            waiting[next_char].swear_words_numbers[waiting[next_char].count++] = waiting_index;

        }

    }

    printf("NO");
    for(int itr = 0; itr < 128; itr++){
        delete[] waiting[itr].swear_words_numbers;
    }

    delete[] swear_words;
    return 0;

}