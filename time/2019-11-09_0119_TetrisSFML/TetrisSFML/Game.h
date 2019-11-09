#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

struct Item
{
    static const int size_px = 30;

    Item()
    {
        value = 0;
        rect.setSize(sf::Vector2f(size_px, size_px));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(size_px * 0.05);
    }

    void setPosition(unsigned row, unsigned col)
    {
        rect.setPosition(col * size_px, row * size_px);
    }

    char value;
    sf::RectangleShape rect;

};

class Game
{
    const unsigned rows = 16;
    const unsigned cols = 8;
    std::vector<std::vector<Item>> m_matrix;
    std::unordered_map<unsigned char, sf::Color> m_colors;


public:
    Game();
    void setTime(sf::Time time);
    void setKeyEvent(sf::Event keyEvent);
    void resume();
    void pause();
    void drawOn(sf::RenderWindow& window);
};
