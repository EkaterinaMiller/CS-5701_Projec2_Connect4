#include "human_player.h"
#include "helpers.h"

void Human_player::makeaMove(int min, int max){
    std::cout << "Human turn. Enter column (" << min << "-" << max << "): ";
    int userChoose = getUserInput(1,7);
    while (!mConnectBoard.placeToken(mToken,userChoose-1)){
        std::cout << "This position is full. Choose another column.\n";
        userChoose = getUserInput(1,7);
    }
}
