#ifndef PLAYER_H
#define PLAYER_H 
#include "connect4.h"   

class Player
{
public:
    Player(Connect4 & board, char token) : mConnectBoard(board), mToken(token) {}
    char getToken() const {return mToken;}
    void setToken(char t){mToken=t; }
    virtual void makeaMove(int min, int max) = 0; //pure virtual function
protected:    
    Connect4 & mConnectBoard;
    char mToken{' '};
};
#endif