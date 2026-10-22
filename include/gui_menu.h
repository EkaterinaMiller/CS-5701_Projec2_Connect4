#ifndef MENU_H
#define MENU_H

#include "gui_button.h"
#include "gui_states.h"

class Menu
{
public:
    Menu();
    ~Menu(){};

    void handleInput(sf::RenderWindow& mWindow);
    void update(double elapsedTime, sf::RenderWindow& mWindow);
    void render(sf::RenderWindow& mWindow);


private:
    State mGameState;
    Button mStart;
   
};
#endif