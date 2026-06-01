#include "../include/human_player.h"
#include "../include/helpers.h"
#include <chrono>

void Human_player::makeaMove(int min, int max){
    auto start = std::chrono::steady_clock::now();
    std::cout << "Human turn. Enter column (" << min+1 << "-" << max+1 << "): ";
    int userChoose = getUserInput(min+1, max+1);
    while (!mConnectBoard.placeToken(mToken,userChoose-1)){
        std::cout << "This position is full. Choose another column.\n";
        userChoose = getUserInput(min+1, max+1);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    mMoveTimes.push_back(elapsed.count());
}
