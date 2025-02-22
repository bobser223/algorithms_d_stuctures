#include<string>
#include <iostream>


struct swear_word{
    size_t counter = 0;
    std::string word;
};



int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);


    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto swear_words = new swear_word[n];
    std::string text;

    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, swear_words[i].word, '\n');
//        std::cout << swear_words[i].word << "<- word " << std::endl;
    }

    std::getline(std::cin, text);

//    std::cout << text << std::endl;


    for (int i = 0; i < text.size(); i++){
        for (int j = 0; j < n; j++){
            if (swear_words[j].word[swear_words[j].counter] == text[i]){
                swear_words[j].counter ++;
                if (swear_words[j].counter == swear_words[j].word.size()){
                    printf("YES %d", i+1);
                    return 0;
                }
            }
        }

    }

    printf("NO");

    delete[] swear_words;

}