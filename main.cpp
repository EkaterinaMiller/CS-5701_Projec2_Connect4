#include "connect4.h"
#include "AI_player.h"
#include <iostream>
#include <array>
int getUserInput(int min, int max);
int main()
{
    //Connect4 * game = new Connect4;
    Connect4 game;
    AI_player ai(game);
    while (!game.isDone()){
        game.printBoard();
        while(1){
            int userChoose = getUserInput(1,7);
            if (!game.placeToken('X',userChoose)){
                std::cout << "This position is full\n";
            }else{
                break;
            }
        }
        game.printBoard();
        if (game.isWin('X'))
        {
            std::cout<<"Human won\n";
            break;
        }
        if (game.isFull())
        {
            std::cout<<"It is a tie!\n";
            break;
        }
        //computer turn

    }
    return 0;
}
int getUserInput(int min, int max)
{
    int input;
    do{
        std::cout<<"Human turn. Enter column (1-7): ";
    }while(input<1 || input >7);
    return input;

}