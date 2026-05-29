#include "AI_player.h"

AI_player::AI_player(Connect4 & board){
    mConnectBoard=board;
}

void AI_player::makeaMove(){
    while(1){
        int move = rand()%NUM_COL;//returns 0-6
        if (mConnectBoard.placeToken('mToken',move)){
            break;
        }
    }

}