#include "stdafx.h"
#include "PauseMessage.h"

PauseMessage::PauseMessage()
{
    sf::Text pauseMessage;
    pauseMessage.setCharacterSize(40);
    pauseMessage.setPosition(170.f, 150.f);
    pauseMessage.setFillColor(sf::Color::White);
    pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");
}

void PauseMessage::setFont(const sf::Font& font)
{
    pauseMessage.setFont(font);
}

void PauseMessage::setString(const sf::String& string)
{
    pauseMessage.setString(string);
}

void PauseMessage::draw(sf::RenderWindow& window) const
{
    window.draw(pauseMessage);
}
