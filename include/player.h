#ifndef PLAYER_H
#define PLAYER_H 
#include "connect4.h"  
#include <vector> 

class Player
{
public:
    Player(Connect4 & board, char token) : mConnectBoard(board), mToken(token) {}
    char getToken() const {return mToken;}
    void setToken(char t){mToken=t; }
    virtual void makeaMove(int min, int max) = 0; //pure virtual function
    virtual ~Player() = default;
    double printMoveTimes() const {
        std::cout << "Move times for player " << mToken << ": ";
        if (mMoveTimes.empty()) {
            std::cout << "none\nAverage: 0 ms" << std::endl;
            return -1.0; // Return -1 to indicate no moves were made
        }
        double total{0.0};
        for (size_t i = 0; i < mMoveTimes.size(); ++i) {
            total += mMoveTimes[i];
            std::cout << mMoveTimes[i] << " ,";
        }
        return total / mMoveTimes.size();
    }
protected:    
    Connect4 & mConnectBoard;
    char mToken{' '};
    std::vector<double> mMoveTimes;
};
#endif