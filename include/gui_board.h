#ifndef BOARD_H
#define BOARD_H
#include "gui_button.h"
#include "connect4.h"
class Board : public Connect4
{
public:
    Board();
    ~Board(){};

    void handleInput(const sf::Event& e, sf::RenderWindow& window);
    void update(double elapsedTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);


private:
    sf::Vector2f mGameAreaPosition{350, 0};
    sf::Vector2f mGameAreaSize{650, 800};
    sf::Texture mTexture;
    sf::RectangleShape mBackGround;
    sf::RectangleShape mBoard;  
};
#endif