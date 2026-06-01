#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "connect4.h"
#include "player.h"
#include <iostream>
#include <random>
#include <time.h>

// const int MAX_DEPTH = 5;

class AI_player: public Player
{
public:
    AI_player(Connect4 & board, char token);
    virtual void makeaMove(int min, int max) override;
    void setDepth(int depth) { mDepth = depth; }
    int getDepth() const { return mDepth; }
    virtual ~AI_player() = default;
private:
    //std::mt19937 mGenerator;
    float evaluateBoard(const Connect4 & board, int turn) const;
    float playAtRandom(Connect4 board, int turn=0) const;
    int findBestMove(int min, int max) const;
    float minMove(Connect4 &board, int depth) const;
    float maxMove(Connect4 &board, int depth) const;
    void makeRandomMove(Connect4 &board, int min, int max, char playerToken);

    int mDepth{5};
    char mOponentToken{(mToken == 'X') ? 'O' : 'X'};

    std::vector<float> mMoveTimes;

};
#endif