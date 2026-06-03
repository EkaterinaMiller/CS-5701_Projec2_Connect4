/**
 * @file main.cpp
 * @author Ekaterina Miller
 * @brief Main function for the CLI Connect4 game
 * @date 2026-06-02
 * 
 */
#include "../include/connect4.h"
#include "../include/player.h"
#include "../include/human_player.h"
#include "../include/AI_player.h"
#include <iostream>
#include <array>
#include "../include/helpers.h"

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
    int depth{10};  
    bool pruning{false};
    bool ai1{false};
    bool ai2{false};    
    switch (choice)
    {    
    case 1:
        player[0] = new Human_player(game, 'X');
        player[1] = new Human_player(game, 'O');
        break;
    case 2:
        getParameters(depth, pruning);
        player[0] = new Human_player(game, 'X');
        player[1] = new AI_player(game, 'O', 'X', depth, pruning);
        ai2 = true;
        break;
    case 3:
        getParameters(depth, pruning);
        player[0] = new AI_player(game, 'X', 'O', depth, pruning);
        player[1] = new Human_player(game, 'O');
        ai1 = true;
        break;
    case 4:
        getParameters(depth, pruning);
        player[0] = new AI_player(game, 'X', 'O', depth, pruning);
        player[1] = new AI_player(game, 'O', 'X', depth, pruning);
        ai1 = true;
        ai2 = true;
        break;
    default:
        std::cout << "Exiting...\n";
        return 0;
    }
    int turn = 0;
    game.printBoard();
    while(1){
        std::cout << "Player " << player[turn]->getToken() << "'s turn.\n";
        player[turn]->makeaMove(0,6);
        game.printBoard();
        if (game.isWin(player[turn]->getToken()))
        {
            std::cout<<"Player "<<player[turn]->getToken()<<" won!\n";
            break;
        }
        if (game.isFull())
        {
            std::cout<<"It is a tie!\n";
            break;   
        }
        // game.printBoard();
        turn = (turn + 1) % 2; //switch player
    }
    std::cout << "Player " << player[0]->getToken() << " average move time: " 
            << player[0]->printMoveTimes() << " ms" << std::endl;
    std::cout << "Player " << player[1]->getToken() << " average move time: " 
            << player[1]->printMoveTimes() << " ms" << std::endl  ;
    if (ai1) {
        std::cout << "AI Player " << player[0]->getToken() << " average explored nodes: " 
                << dynamic_cast<AI_player*>(player[0])->averageExploredNodes() << std::endl;
    }
    if (ai2) {
        std::cout << "AI Player " << player[1]->getToken() << " average explored nodes: " 
                << dynamic_cast<AI_player*>(player[1])->averageExploredNodes() << std::endl;
    }   
    // Clean up dynamically allocated players
    delete player[0];
    delete player[1];   
    return 0;
}
