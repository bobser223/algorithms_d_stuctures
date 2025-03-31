#include <queue>
#include <iostream>


using std::cin, std::cout, std::endl;
int n;

bool isBigger(int a, int b){ // a > b
    if (a == 0 && b == n-1) return true;
    if (b == 0 && a == n-1) return false;
    return (a > b);
}

void game(std::queue<int>& pl1, std::queue<int>& pl2){
    int counter = 0;
    while(!pl1.empty() && !pl2.empty()){

        if (counter == 200000){
            cout << "draw" << endl;
            return;
        }

        int p1_card = pl1.front();pl1.pop();
        int p2_card = pl2.front();pl2.pop();

        if (isBigger(p1_card, p2_card)){
            pl1.push(p1_card);
            pl1.push(p2_card);
        } else{
            pl2.push(p1_card);
            pl2.push(p2_card);
        }

        counter++;
    }
    cout << (pl1.empty()? "second " : "first ") << counter << endl;

}



int main(){
    int buff;
    cin >> n;
    std::queue<int> player1, player2;
    for(int i = 0; i < n/2; i++){
        cin >> buff;
        player1.push(buff);
    }

    for(int i = 0; i < n/2; i++){
        cin >> buff;
        player2.push(buff);
    }

    game(player1, player2);

}