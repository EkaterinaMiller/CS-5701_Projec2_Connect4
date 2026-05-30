#include "connect4.h"
#include "player.h"
#include "human_player.h"
#include "AI_player.h"
#include <iostream>
#include <array>
int getUserInput(int min, int max);
int main()
{
    Connect4 game; //creat a board
    std::cout << "Welcome to Connect4!\n";
    std::cout << "How do you want to play?\n";
    std::cout << "1. Human vs Human\n";
    std::cout << "2. Human vs Computer\n";
    std::cout << "3. Computer vs Human\n";
    std::cout << "4. Computer vs Computer\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice (1-5): ";
    int choice = getUserInput(1,5);

    Player * player[2];
    switch (choice)
    {    
    case 1:
        player[0] = new Human_player(game, 'X');
        player[1] = new Human_player(game, 'O');
        break;
    case 2:
        player[0] = new Human_player(game, 'X');
        player[1] = new AI_player(game, 'O');
        break;
    case 3:
        player[0] = new AI_player(game, 'X');
        player[1] = new Human_player(game, 'O');
        break;
    case 4:
        player[0] = new AI_player(game, 'X');
        player[1] = new AI_player(game, 'O');
        break;
    default:
        std::cout << "Exiting...\n";
        return 0;
    }
    int turn = 0;
    while (!game.isDone()){
        game.printBoard();
        while(1){
            std::cout << "Player " << player[turn]->getToken() << "'s turn.\n";
            player[turn]->makeaMove(0,6);
            game.printBoard();
            if (game.isWin(player[turn]->getToken()))
            {
                std::cout<<"Player "<<player[turn]->getToken()<<" won!\n";
                return 0;
            }
            if (game.isFull())
            {
                std::cout<<"It is a tie!\n";
                return 0;   
            }
            // game.printBoard();
            turn = (turn + 1) % 2; //switch player
        }
    }
    return 0;
}
