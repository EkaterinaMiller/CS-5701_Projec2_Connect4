#include "../include/gui_game.h"

Game::Game()
{
    mGameState = START;
}

//Handle events from input devices and the window
void Game::handleInput(sf::RenderWindow& window)
{

    while(const std::optional<sf::Event> event =window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            // Close window button clicked.
            window.close();
        }
        switch (mGameState)
        {
        case welcome:
//std::cout<<"Game::handleInput case welcome" <<std::endl;
            mGameState = mWelcomeScreen.handleInput(*event, window);
            break;
        case game:
//std::cout<<"Game::handleInput case game" <<std::endl;
            mGameState = mGame.handleInput(*event, window);
            break;
        case results:
//std::cout<<"Game::handleInput case result" <<std::endl;
            mGameState=mResults.handleInput(*event, window);
            break;
        case quit:
//std::cout<<"Game::handleInput case quit" <<std::endl;
            window.close();
            break;            
        }
    }
}

//Update objects in the scene
void Game::update(double elapsedTime, sf::RenderWindow& window)
{
    switch (mGameState)
        {
        case welcome:
//std::cout<<"Game::update case welcome" <<std::endl;
            mWelcomeScreen.update();
            break;
        case game:
//std::cout<<"Game::update case game" <<std::endl;
            mGame.update(elapsedTime, window);
            break;
        case results:
//std::cout<<"Game::update case result" <<std::endl;
            mResults.update();
            break;
        case quit:
//std::cout<<"Game::update case quit" <<std::endl;
            window.close();
            break;            
        }
}


//Render objects from the scene onto the window
void Game::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    //mWindow.draw(mCherryPlant);
    switch (mGameState)
        {
        case welcome:
            mWelcomeScreen.render(window);
            break;
        case game:
            mGame.render(window);
            break;
        case results:
            mResults.render(window);
            break;
        case quit:
            break;          
        }
    window.display();
}

//Check if game is done, right now, we just checked if window is still open
// bool Game::isDone() const
// {
//     return (!mWindow.isOpen());
// }