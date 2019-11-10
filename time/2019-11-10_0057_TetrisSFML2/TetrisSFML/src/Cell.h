#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Cell
{
    static const unsigned s_bodySize_px = 26;
    static const unsigned s_borderSize_px = 6;
    static const unsigned s_size = s_bodySize_px + s_borderSize_px;

public:
    sf::Color m_color;
    bool m_isVisible;

    Cell();
    Cell(bool isVisible, sf::Color color = sf::Color::Red);

    void draw(sf::RenderWindow& window, sf::Vector2u cellPos) const;
    sf::Color getColor() const;
    bool isVisible() const;
    void setVisible(bool b);
    static const unsigned getSize();
};
