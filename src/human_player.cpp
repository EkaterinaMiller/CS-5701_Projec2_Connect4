#include "../include/human_player.h"
#include "../include/helpers.h"

void Human_player::makeaMove(int min, int max){
    std::cout << "Human turn. Enter column (" << min+1 << "-" << max+1 << "): ";
    int userChoose = getUserInput(min+1, max+1);
    while (!mConnectBoard.placeToken(mToken,userChoose-1)){
        std::cout << "This position is full. Choose another column.\n";
        userChoose = getUserInput(min+1, max+1);
    }
}
