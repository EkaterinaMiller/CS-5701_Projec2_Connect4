#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "connect4.h"
#include "player.h"
#include <iostream>
#include <random>
#include <time.h>

const bool PRUNING = true; // Set to true to enable alpha-beta pruning, false for minimax without pruning

class AI_player: public Player
{
public:
    AI_player(Connect4 & board, char token);
    virtual void makeaMove(int min, int max) override;
    void setDepth(int depth) { mDepth = depth; }
    int getDepth() const { return mDepth; }
    void setPruning(bool usePruning) { mUsePruning = usePruning; }
    bool getPruning() const { return mUsePruning; }
    virtual ~AI_player() = default;
private:
    //std::mt19937 mGenerator;
    float evaluateBoard(const Connect4 & board) const;
    float playAtRandom(Connect4 board, int turn=0) const;
    int findBestMove(int min, int max, bool pruning) const;
    float minMove(Connect4 &board, int depth, bool pruning, float alpha, float beta) const;
    float maxMove(Connect4 &board, int depth, bool pruning, float alpha, float beta) const;
    void makeRandomMove(Connect4 &board, int min, int max, char playerToken);

    int mDepth{10};
    char mOponentToken{(mToken == 'X') ? 'O' : 'X'};
    bool mUsePruning{PRUNING};

};
#endif