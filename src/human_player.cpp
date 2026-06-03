/**
 * @file human_player.cpp
 * @author Ekaterina Miller
 * @brief Implementation of the Human_player class for Connect4 game, 
 *        allowing user input for moves
 * @date 2026-06-02
 * 
 */
#include "../include/human_player.h"
#include "../include/helpers.h"
#include <chrono>
/**
 * @brief Makes a move for the human player
 * @param min minimum available move column index
 * @param max maximum available move column index
 */
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
