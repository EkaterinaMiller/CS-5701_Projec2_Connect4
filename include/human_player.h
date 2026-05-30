#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "connect4.h"
#include "player.h" 

class Human_player: public Player
{
public:
    Human_player(Connect4 & board, char token) : Player(board, token) {}
    virtual void makeaMove(int min, int max) override; 
    virtual ~Human_player() = default;
};
#endif    