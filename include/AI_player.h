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
    AI_player(Connect4 & board, char token, char oponentToken, int depth = 10, bool usePruning = PRUNING);
    virtual void makeaMove(int min, int max) override;
    void setDepth(int depth) { mDepth = depth; }
    int getDepth() const { return mDepth; }
    void setPruning(bool usePruning) { mUsePruning = usePruning; }
    bool getPruning() const { return mUsePruning; }
    double averageExploredNodes() const;
    const std::vector<int> &getExploredNodes() const { return mExploredNodes; }
    float evaluateBoard(const Connect4 & board) const;
    int findBestMove(int min, int max, bool pruning, int &numNodes) const;
    float minMove(Connect4 &board, int depth, bool pruning, float alpha, float beta, int &numNodes) const;
    float maxMove(Connect4 &board, int depth, bool pruning, float alpha, float beta, int &numNodes) const;
    //float playAtRandom(Connect4 board, int turn=0) const;
    //void makeRandomMove(Connect4 &board, int min, int max, char playerToken);
    virtual ~AI_player()=default; 
private:

    char mOponentToken{' '};
    int mDepth{10};
    bool mUsePruning{PRUNING} ;
    std::vector<int> mExploredNodes; // Store the number of nodes explored at each move

};
#endif