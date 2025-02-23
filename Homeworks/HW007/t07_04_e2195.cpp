#include <stdexcept>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>

class StringSet{
protected:
    int size;
    int count;
    std::string* arr;

    void make_arr_empty(){
        for (int i = 0; i < size; i++){
            arr[i] = "EMPTY";
        }
    }

    static void lower(std::string &s){
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return tolower(c);
        });
    }

    static bool is_prime(int num){
        if (num < 2) return false;
        for (int i = 2; i <= static_cast<int>(std::sqrt(num)); i++){
            if (num % i == 0)
                return false;
        }
        return true;
    }


    void rehash(){
        int old_size = size;
        std::string* old_arr = arr;

        size = 2 * size + 1;
        while(!is_prime(size)){
            size = 2 * size + 1;
        }

        arr = new std::string[size];
        make_arr_empty();

        count = 0;
        for (int i = 0; i < old_size; i++){
            if (old_arr[i] != "EMPTY")
                add(old_arr[i]);
        }

        delete[] old_arr;
    }


public:
    StringSet(int new_size=7){
        size = new_size;
        count = 0;
        arr = new std::string[size];
        make_arr_empty();
    }

    ~StringSet(){
        delete[] arr;
    }



    void add(std::string& str){

        if (size*0.7 < count) rehash();

        lower(str);

        int position = hash(str);
        while (arr[position] != "EMPTY" ){
            if (arr[position] == str)
                return;
            position = (position + 1) % size;
        }

        arr[position] = str;
        count++;
    }

//    void add(std::string&& str){ // rvalue method for testing
//
//        lower(str);
//
//        int position = hash(str);
//        while (arr[position] != "EMPTY" ){
//            if (arr[position] == str)
//                return;
//            position = (position + 1) % size;
//        }
//
//        arr[position] = str;
//        count++;
//    }

    bool is_in(std::string& str){

        lower(str);

        int position = hash(str);
        while (arr[position] != "EMPTY" ){
            if (arr[position] == str)
                return true;
            position = (position + 1) % size;
        }

        return false;
    }

    bool is_in(std::string&& str){

        lower(str);

        int position = hash(str);
        while (arr[position] != "EMPTY" ){
            if (arr[position] == str)
                return true;
            position = (position + 1) % size;
        }

        return false;
    }



    int hash(const std::string &str){
        int const_prime = 31;
        unsigned int h = 0;
        for (size_t i = 0; i < str.length(); i++) {
            h = h * const_prime + static_cast<int>(str[i]);
        }
        return h % this->size;
    }


    int get_size() const{
        return count;
    }

    void print(){
        for (int i = 0; i < size; i++){
            if (arr[i] != "EMPTY")
                std::cout << arr[i] << " ";

        }
        printf("\n");
    }
    void debug_print(){
        for (int i = 0; i < size; i++){

            std::cout << arr[i] << " ";

        }
        printf("\n");
    }

    std::string* all_values(){
        auto *result = new std::string[count];
        int j = 0;
        for (int i = 0; i < size; i++){
            if (arr[i] != "EMPTY")
                result[j++] = arr[i];
        }
        std::sort(result, result + count);
        return result;
    }

};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    StringSet set;
    int n, M;
    std::cin >> n >> M;
    std::cin.ignore();
    std::string buffer;
    for (int i = 0; i < n; i++){
        std::cin>> buffer;
        set.add(buffer);
    }

    std::string text, line;
    for (int i = 0; i < M+1; i++) {
        getline(std::cin, line);
//        std::cout << line << std::endl;
        text += line + " ";
    }

//    std::cout << text << std::endl;

    for (char &ch : text) {

        if (!isalpha(ch) && !isspace(ch)) {
            ch = ' ';
        }
    }



    std::istringstream iss(text);
    std::string word;
    std::vector<std::string> words;

    StringSet set2;
    while (iss >> word) {
//        std::cout << word << std::endl;
        set2.add(word);
        if (!set.is_in(word)){
            std::cout << "Some words from the text are unknown." << std::endl;
            return 0;

        }

    }

//
//    std::cout << set.get_size() <<std::endl;
//    std::cout << set2.get_size() <<std::endl;

    if (set.get_size() > set2.get_size()){
        std::cout << "The usage of the vocabulary is not perfect." << std::endl;
        return 0;
    }


    std::cout << "Everything is going to be OK." << std::endl;



}