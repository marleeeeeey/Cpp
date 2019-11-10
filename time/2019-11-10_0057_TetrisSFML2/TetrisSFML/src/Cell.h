#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Cell
{
public:
    sf::Color m_color;
    bool m_isVisible;

    Cell();
    Cell(sf::Color color, bool isVisible);

    void draw(sf::RenderWindow& window, sf::Vector2u cellPos) const;
    sf::Color getColor() const;
    bool isVisible() const;
};
