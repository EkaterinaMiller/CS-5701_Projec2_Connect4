#include "../include/gui_button.h"

Button::Button() : Button("Push me!", {300.f, 100.f}, {300.f, 100.f}, sf::Color::White)
{
}
//Constructor that sets button label to s, button position to the position,  button size to size (given in pixels), and button color to color.
Button::Button(std::string s, sf::Vector2f position, sf::Vector2f size, sf::Color color): 
    mButtonColor(color), mPosition(position), mBtnState(normal), mText(mFont)
{
    if (!mTexture.loadFromFile("assets/button.png"))
    {
        std::cerr<<"Error opening file\n";
        exit(1);
    }
    //create sprite that look like a button
    mButton.setTexture(&mTexture);
    mButton.setSize(size);
    //get size of image
    sf::Vector2f buttonSize=mButton.getSize();
    mButton.setOrigin({buttonSize.x/2.f, buttonSize.y/2.f});
    //set position
    mButton.setPosition(mPosition);
    //choose color
    mButton.setFillColor(mButtonColor);
    //set size as a ration of original size
    //Make label

    if (!mFont.openFromFile("assets/college.ttf"))
    {
        std::cerr<<"Error opening file\n";
        exit(2);
    }
    mText.setFont(mFont);
    //choose the font size based on button size (I choose half)
    unsigned int fontSize = mButton.getGlobalBounds().size.y/2;
    mText.setCharacterSize(fontSize);
    //set label
    mText.setString(s);
    //set origin to the middle
    mText.setOrigin({mText.getGlobalBounds().size.x/2, mText.getGlobalBounds().size.y/2});
    //set position at the middle of the button
    mText.setPosition({mPosition.x, mPosition.y-fontSize/4});
    mText.setFillColor(mTextNormal);
    mLight = false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mText, states);
}

bool Button::handleInput(const sf::Event& e, sf::RenderWindow& window)
{
    const sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    const sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixelPos);
    const bool mouseInButton = mButton.getGlobalBounds().contains(mousePosition);

    if (e.getIf<sf::Event::MouseMoved>())
    {
        mBtnState = mouseInButton ? hovered : normal;
    }

    if (const auto* mouseButtonPressed = e.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            if (mouseInButton)
            {
                mBtnState = clicked;
                return true;
            }
            mBtnState = normal;
        }
    }

    if (const auto* mouseButtonReleased = e.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseButtonReleased->button == sf::Mouse::Button::Left)
        {
            mBtnState = mouseInButton ? hovered : normal;
        }
    }

    return false;
}

void Button::update()
{
    switch (mBtnState)
    {
    case normal:
        mButton.setRotation(sf::degrees(0.f));
        mText.setFillColor(mTextNormal);
        break;
    case hovered:
        mButton.setRotation(sf::degrees(0.f));
        mText.setFillColor(mTextHover);
        break;
    case clicked:
        mButton.setRotation(sf::degrees(180.f));
        mText.setFillColor(mTextHover);
        break;
    }
}

void Button::setText(const std::string& s)
{
    mText.setString(s);
    unsigned int fontSize = mButton.getGlobalBounds().size.y/2;
    mText.setCharacterSize(fontSize);
    //set label
    mText.setString(s);
    //set origin to the middle
    mText.setOrigin({mText.getGlobalBounds().size.x/2, mText.getGlobalBounds().size.y/2});
    //set position at the middle of the button
    mText.setPosition({mPosition.x, mPosition.y-fontSize/4});
}

void Button::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mButton.setPosition(mPosition);
    unsigned int fontSize = mButton.getGlobalBounds().size.y/2;
    mText.setCharacterSize(fontSize);
    //set origin to the middle
    mText.setOrigin({mText.getGlobalBounds().size.x/2, mText.getGlobalBounds().size.y/2});
    //set position at the middle of the button
    mText.setPosition({mPosition.x, mPosition.y-fontSize/4});
}

void Button::setSize(sf::Vector2f size)
{
    mButton.setSize(size);
    //get size of image
    sf::Vector2f buttonSize=mButton.getSize();
    mButton.setOrigin({buttonSize.x/2.f, buttonSize.y/2.f});
    //set position
    mButton.setPosition(mPosition);

    //choose the font size based on button size (I choose half)
    unsigned int fontSize = mButton.getGlobalBounds().size.y/2;
    mText.setCharacterSize(fontSize);
    //set origin to the middle
    mText.setOrigin({mText.getGlobalBounds().size.x/2, mText.getGlobalBounds().size.y/2});
    //set position at the middle of the button
    mText.setPosition({mPosition.x, mPosition.y-fontSize/4});
}

void Button::setColor(sf::Color btnColor)
{
    mButtonColor = btnColor;
    mButton.setFillColor(mButtonColor);
}