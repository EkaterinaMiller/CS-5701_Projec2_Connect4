#include "../include/gui_board.h"
Board::Board()
{
    mBackGround.setFillColor(sf::Color({243, 242, 250}));
    mBackGround.setPosition(mGameAreaPosition);
    mBackGround.setSize(mGameAreaSize);
    if (!mTexture.loadFromFile("assets/connect4_nobg.png"))
    {
        std::cerr<<"Error opening file\n";
        exit(1);
    }
    //create sprite that look like a button
    mBoard.setTexture(&mTexture);
    float boardWidth = mGameAreaSize.x*11.f/13.f;
    float boardHight =  boardWidth*mTexture.getSize().y/mTexture.getSize().x;
    mBoard.setSize({boardWidth, boardHight});
    mBoard.setPosition({mGameAreaPosition.x+mGameAreaSize.x*1/13, 200});
}
void Board::setPosition(sf::Vector2f position)
{
    mGameAreaPosition = position;
    mBackGround.setPosition(mGameAreaPosition);
    mBoard.setPosition({mGameAreaPosition.x+mGameAreaSize.x*1/13, 200});
}
void Board::setSize(sf::Vector2f size)
{
    mGameAreaSize=size;
    mBackGround.setSize(mGameAreaSize);
    float boardWidth = mGameAreaSize.x*11.f/13.f;
    float boardHight =  boardWidth*mTexture.getSize().y/mTexture.getSize().x;
    mBoard.setSize({boardWidth, boardHight});
    mBoard.setPosition({mGameAreaPosition.x+mGameAreaSize.x*1/13, 200});
}
void Board::handleInput(const sf::Event& e, sf::RenderWindow& window)
{

}
void Board::update(double elapsedTime, sf::RenderWindow& window)
{

}
void Board::render(sf::RenderWindow& window)
{
    window.draw(mBackGround);
    window.draw(mBoard);
}