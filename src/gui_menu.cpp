#include "../include/gui_menu.h"
Menu::Menu():mTitle(mFont), mInstruction(mFont), mResult(mFont)
{
    const sf::Vector2f BUTTON_SIZE{mMenuSize.x*5/7, 50};
    mMode = UKN;
    mMenu.setPosition(mPosition);
    mMenu.setFillColor(sf::Color({203, 198, 245}));
    mMenu.setSize(mMenuSize);

    if (!mFont.openFromFile("assets/college.ttf"))
    {
        std::cerr<<"Error opening file\n";
        exit(2);
    }
    mTitle.setFont(mFont);
    mTitle.setCharacterSize(mMenuSize.x/7);
    mTitle.setString("Connect 4");
    mTitle.setFillColor(sf::Color({21, 3, 148}));
    mTitle.setOrigin({mTitle.getGlobalBounds().size.x/2, mTitle.getGlobalBounds().size.y/2});
    mTitle.setPosition({mPosition.x + mMenuSize.x/2, mPosition.y + 30});

    mInstruction.setFont(mFont);
    mInstruction.setString("Choose the mode below");
    mInstruction.setFillColor(sf::Color({51, 37, 153}));
    mInstruction.setCharacterSize(mMenuSize.x/15);
    mInstruction.setOrigin({mInstruction.getGlobalBounds().size.x/2, mInstruction.getGlobalBounds().size.y/2});
    mInstruction.setPosition({mPosition.x + mMenuSize.x/2, mPosition.y + 80});

    mHumanVsHuman.setText("Human vs Human");
    mHumanVsHuman.setColor(sf::Color({42, 16, 232}));
    mHumanVsHuman.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 180});
    mHumanVsHuman.setSize(BUTTON_SIZE);

    mHumanVsAi.setText("Human vs AI");
    mHumanVsAi.setColor(sf::Color({42, 16, 232}));
    mHumanVsAi.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 250});
    mHumanVsAi.setSize(BUTTON_SIZE);

    mAiVsHuman.setText("AI vs Human");
    mAiVsHuman.setColor(sf::Color({42, 16, 232}));
    mAiVsHuman.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 320});
    mAiVsHuman.setSize(BUTTON_SIZE);

    mAiVsAi.setText("Ai vs Ai");
    mAiVsAi.setColor(sf::Color({42, 16, 232}));
    mAiVsAi.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 390});
    mAiVsAi.setSize(BUTTON_SIZE);

    mResult.setFont(mFont);
    mResult.setString(MODE[mMode]);
    mResult.setFillColor(sf::Color({51, 37, 153}));
    mResult.setCharacterSize(mMenuSize.x/15);
    mResult.setPosition({mPosition.x + 15, mPosition.y + 450});

    mStart.setText("Start");
    mStart.setColor(sf::Color::Blue);
    mStart.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + mMenuSize.y-100});
    mStart.setSize({mMenuSize.x/2, 50});

}
void Menu::setSize(sf::Vector2f size)
{
    mMenuSize=size;
    const sf::Vector2f BUTTON_SIZE{mMenuSize.x*5/7, 50};

    mMenu.setSize(mMenuSize);

    mTitle.setCharacterSize(mMenuSize.x/7);
    mTitle.setOrigin({mTitle.getGlobalBounds().size.x/2, mTitle.getGlobalBounds().size.y/2});
    mTitle.setPosition({mPosition.x + mMenuSize.x/2, mPosition.y + 30});

    mInstruction.setCharacterSize(mMenuSize.x/15);
    mInstruction.setOrigin({mInstruction.getGlobalBounds().size.x/2, mInstruction.getGlobalBounds().size.y/2});
    mInstruction.setPosition({mPosition.x + mMenuSize.x/2, mPosition.y + 80});

    mHumanVsHuman.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 180});
    mHumanVsHuman.setSize(BUTTON_SIZE);
    mHumanVsAi.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 250});
    mHumanVsAi.setSize(BUTTON_SIZE);
    mAiVsHuman.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 320});
    mAiVsHuman.setSize(BUTTON_SIZE);
    mAiVsAi.setPosition({mPosition.x+ mMenuSize.x/2, mPosition.y + 390});
    mAiVsAi.setSize(BUTTON_SIZE);

    mResult.setCharacterSize(mMenuSize.x/15);
    mResult.setPosition({mPosition.x + 15, mPosition.y + 450});

    mStart.setSize({mMenuSize.x/2, 50});
    mStart.setPosition({mPosition.x+ mMenuSize.y*0.2f, mPosition.y + mMenuSize.y-100});
}
void Menu::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mMenu.setPosition(mPosition);

    mTitle.setPosition({mPosition.x + mMenuSize.x/2, mPosition.y +mMenuSize.y/2});

    mInstruction.setPosition({mPosition.x + mMenuSize.x/2, mPosition.y + 50});

    mResult.setPosition({mPosition.x + 15, mPosition.y + 450});

    mStart.setPosition({mPosition.x+ mMenuSize.y*0.2f, mPosition.y + mMenuSize.y-100});
}

State Menu::handleInput(const sf::Event& e, sf::RenderWindow& window)
{
    if (mHumanVsHuman.handleInput(e, window)){
        mMode = HvsH;
    }
    if(mHumanVsAi.handleInput(e, window)){
        mMode = HvsA;
    }
    if(mAiVsHuman.handleInput(e, window)){
        mMode = AvsH;
    }
    if(mAiVsAi.handleInput(e, window)){
        mMode = AvsA;
    }

    if(mStart.handleInput(e, window)){
        return SETUP;
    }
    return START;
}

void Menu::update(sf::RenderWindow& window)
{
    mHumanVsHuman.update();
    mHumanVsAi.update();
    mAiVsHuman.update();
    mAiVsAi.update();
    mResult.setString(MODE[mMode]);
    mStart.update();
}
void Menu::render(sf::RenderWindow& window)
{
    window.draw(mMenu);
    window.draw(mTitle);
    window.draw(mInstruction);
    window.draw(mHumanVsHuman);
    window.draw(mHumanVsAi);
    window.draw(mAiVsHuman);
    window.draw(mAiVsAi);
    window.draw(mResult);
    window.draw(mStart);
}
