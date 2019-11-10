#pragma once

#include <SFML/Graphics.hpp>

struct Cell
{
    sf::Color color = sf::Color::Blue;
    bool isVisible = false;

    inline void draw(sf::RenderWindow & window, sf::Vector2u cellPos) const
    {
        if(isVisible)
        {
            float size_px = 20;
            sf::RectangleShape rect({ size_px, size_px });
            rect.setPosition({ cellPos.x * size_px, cellPos.y * size_px });
            rect.setOutlineColor(color);
            rect.setOutlineThickness(2);
            window.draw(rect);
        }
    }
};