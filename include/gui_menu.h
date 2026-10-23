#ifndef MENU_H
#define MENU_H

#include "gui_button.h"
#include "gui_states.h"


class Menu
{
public:
    Menu();
    ~Menu(){};

    State handleInput(const sf::Event& e, sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    Mode getMode(){return mMode;}


private:
    Mode mMode = UKN;
    sf::Vector2f mPosition{0,0};
    sf::Vector2f mMenuSize{200, 500};
    sf::RectangleShape mMenu;
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mInstruction;
    Button mHumanVsHuman;
    Button mHumanVsAi;
    Button mAiVsHuman;
    Button mAiVsAi;
    sf::Text mResult;
    Button mStart;
   
};
#endif