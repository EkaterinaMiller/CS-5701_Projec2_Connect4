/**
 * @file main.cpp
 * @author Ekaterina Miller
 * @brief  This program testing class buton
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * @aknolegment https://code.markrichards.ninja/sfml/how-to-create-simple-buttons-for-your-sfml-game
 * 
 * 
 */

#include "../include/gui_game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "My Game");
    window.setPosition({50,50});
    sf::Vector2f size =static_cast<sf::Vector2f>(window.getSize());
    Game game(size);
   
    sf::Clock clock; 

    while(window.isOpen())
    {
//std::cout<<"Starting while loop"<<std::endl;
        float dt=clock.restart().asSeconds();
        game.handleInput(window);
        game.update(dt, window);
        game.render(window);
    }

    return 0;
}