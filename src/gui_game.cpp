#include "../include/gui_game.h"

Game::Game(sf::Vector2f size):mModeMessage(mFont), mTurnMessage(mFont)
{
    mGameState = START;
    if (!mFont.openFromFile("assets/college.ttf"))
    {
        std::cerr<<"Error opening file\n";
        exit(2);
    }
    mMenu.setSize({size.x*7/20, size.y});
    mBoard.setPosition({size.x*7/20, 0});
    mBoard.setSize({size.x*13/20, size.y});
    mModeMessage.setFont(mFont);
    mTurnMessage.setFont(mFont);
    mModeMessage.setFillColor(sf::Color({203, 198, 245}));
    mTurnMessage.setFillColor(sf::Color({203, 198, 245}));
    mModeMessage.setString("");
    mTurnMessage.setString("");
}

//Handle events from input devices and the window
void Game::handleInput(sf::RenderWindow& window)
{
sf::Vector2f size =static_cast<sf::Vector2f>(window.getSize());
    while(const std::optional<sf::Event> event =window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            // Close window button clicked.
            window.close();
        }
        switch (mGameState)
        {
        case START:
            mGameState = mMenu.handleInput(*event, window);
            break;
        case SETUP:
            setTheGame(size);
            mGameState = GAME;
            break;
        case GAME:
            mBoard.handleInput(*event, window);
            if(mBoard.isDone()){
                mGameState = RESULT;
            }
            break;
        case RESULT:
//std::cout<<"Game::handleInput case result" <<std::endl;
            mGameState=mMenu.handleInput(*event, window);
            break;
        // default:
        //     window.close();
        //     break;            
        }
    }
}

//Update objects in the scene
void Game::update(double elapsedTime, sf::RenderWindow& window)
{
    mMenu.update(window);
    mBoard.update(elapsedTime, window);
    // switch (mGameState)
    //     {
    //     case START:
    //         mMenu.update(elapsedTime, window);
    //         mBoard.update(elapsedTime, window);
    //         break;
    //     case GAME:
    //         mBoard.update(elapsedTime, window);
    //         break;
    //     case RESULT:
    //         mBoard.update(elapsedTime, window);
    //         break;
    //     default:
    //         window.close();
    //         break;            
    //     }
}


//Render objects from the scene onto the window
void Game::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    mMenu.render(window);
    mBoard.render(window);
    window.draw(mModeMessage);
    window.draw(mTurnMessage);
    window.display();
}

void Game::setTheGame(sf::Vector2f size)
{
    mGameMode=mMenu.getMode();
    mModeMessage.setString(MODE[mGameMode]);
    mModeMessage.setOrigin({mModeMessage.getGlobalBounds().size.x/2, mModeMessage.getGlobalBounds().size.y/2});
    mModeMessage.setPosition({size.x*27/40, 50});
     
    switch (mGameMode)
    {    
    case HvsH:
        // player[0] = new Human_player(mGame, 'X');
        // player[1] = new Human_player(mGame, 'O');
        break;
    case HvsA:
        //getParameters(depth, pruning);
        //player[0] = new Human_player(mGame, 'X');
        player[1] = new AI_player(mGame, 'O', 'X', mDepth, mPruning);
        ai2 = true;
        break;
    case AvsH:
        //getParameters(depth, pruning);
        player[0] = new AI_player(mGame, 'X', 'O', mDepth, mPruning);
        //player[1] = new Human_player(mGame, 'O');
        ai1 = true;
        break;
    case AvsA:
        //getParameters(depth, pruning);
        player[0] = new AI_player(mGame, 'X', 'O', mDepth, mPruning);
        player[1] = new AI_player(mGame, 'O', 'X', mDepth, mPruning);
        ai1 = true;
        ai2 = true;
        break;
    }
    int turn = 0;
}