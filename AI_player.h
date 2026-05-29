#include "connect4.h"
#include <iostream>
#include <random>

class AI_player
{
    AI_player(Connect4 & board);
    void setToken(char t){mToken=t; }
    char getToken() const {return mToken;}
    void makeaMove();
private:
    Connect4 & mConnectBoard;
    char mToken{'O'};
};