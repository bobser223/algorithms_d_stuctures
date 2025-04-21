//
// Created by Volodymyr Avvakumov on 15.03.2025.
//

#include "black_red_tree_2.h"


void clearConsole() {
    std::cout << "\033[2J\033[H"; // Clear screen and move cursor to top-left
}


int main(){
    Tree BLT;

//    for (int i = 0; i < 10; i++){
//        BLT.insert(i, i+1);
//    }
//    BLT.printTree();
//
//
//    BLT.pop(2);
//    BLT.printTree();
    std::string curr;
    std::cin >> curr;
    while(curr != "exit"){
        if (curr == "insert"){
            int num, num2;
            std::cin >> num;
            std::cin >> num2;
            BLT.insert(num, num2);
        }


        if (curr == "pop") {
            int num;
            std::cin >> num;
            BLT.pop(num);
        }
        BLT.printTree();
        std::cin >> curr;
        clearConsole();

    }
    printf("bye\n");
}

