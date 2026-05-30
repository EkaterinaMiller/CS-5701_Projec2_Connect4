#include "AI_player.h"



void AI_player::makeaMove(int min, int max){
    while(1){
        //int move = rand()%(max-min+1) + min;//returns min-max
        int move = rand()%max;
        if (mConnectBoard.placeToken(mToken, move)){
            break;
        }
    }

}