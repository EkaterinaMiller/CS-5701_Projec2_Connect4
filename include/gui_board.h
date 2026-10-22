#ifndef BOARD_H
#define BOARD_H
#include "gui_button.h"
#include "gui_states.h"
#include "connect4.h"
class Board : public Connect4
{
public:
    Board();
    ~Board(){};

    void handleInput(sf::RenderWindow& mWindow);
    void update(double elapsedTime, sf::RenderWindow& mWindow);
    void render(sf::RenderWindow& mWindow);


private:
    State mGameState;
    sf::RectangleShape mBoard;  
};
#endif