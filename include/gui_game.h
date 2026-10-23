#ifndef GAME_H
#define GAME_H
#include "gui_states.h"
#include "human_player.h"
#include "player.h"
#include "AI_player.h"
#include "gui_menu.h"
#include "gui_board.h"
#include "human_player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
    Game(sf::Vector2f size);
    ~Game(){};

    void handleInput(sf::RenderWindow& mWindow);
    void update(double elapsedTime, sf::RenderWindow& mWindow);
    void render(sf::RenderWindow& mWindow);
    //bool isDone() const;

private:
    void setTheGame(sf::Vector2f size);
    Mode mGameMode=HvsH;
    State mGameState=START;
    Menu mMenu;
    Board mBoard;
    sf::Font mFont;
    sf::Text mModeMessage;
    sf::Text mTurnMessage;
    Connect4 mGame;
    Player * player[2];
    int mTurn{0};
    int mDepth{10};  
    bool mPruning{false};
    bool ai1{false};
    bool ai2{false};
   
};

#endif