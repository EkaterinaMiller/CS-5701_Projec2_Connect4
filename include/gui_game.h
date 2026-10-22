#ifndef GAME_H
#define GAME_H
#include "gui_states.h"
#include "gui_menu.h"
#include "gui_board.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
    Game();
    ~Game(){};

    void handleInput(sf::RenderWindow& mWindow);
    void update(double elapsedTime, sf::RenderWindow& mWindow);
    void render(sf::RenderWindow& mWindow);
    //bool isDone() const;

private:
    State mGameState=START;
    Menu mMenu;
    Board mBoad;
    Player * player[2];
   
};

#endif