#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Cell
{
public:
    sf::Color m_color;
    bool m_isVisible;

    Cell();
    Cell(bool isVisible, sf::Color color = sf::Color::Red);

    void draw(sf::RenderWindow& window, sf::Vector2u cellPos) const;
    sf::Color getColor() const;
    bool isVisible() const;
    void setVisible(bool b);
};
