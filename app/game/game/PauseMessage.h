#pragma once
#include <SFML/Graphics.hpp>

class PauseMessage
{
    sf::Text pauseMessage;

public:
    PauseMessage();
    void setFont(const sf::Font& font);
    void setString(const sf::String& string);
    void draw(sf::RenderWindow& window) const;
};
