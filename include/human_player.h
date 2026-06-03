/**
 * @file human_player.h
 * @author Ekaterina Miller
 * @brief Human player class for Connect4 game, allowing user input for moves
 * @date 2026-06-02
 * 
 */
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