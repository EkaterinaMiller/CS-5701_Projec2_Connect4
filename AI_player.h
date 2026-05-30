#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "connect4.h"
#include "player.h"
#include <iostream>
#include <random>
//class Connect4;

class AI_player: public Player
{
public:
    AI_player(Connect4 & board, char token) : Player(board, token) {}
    virtual void makeaMove(int min, int max) override;

};
#endif