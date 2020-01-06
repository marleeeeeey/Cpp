#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <deque>

class Info
{
    sf::Vector2u m_pos;
    std::deque<int> scopes;
    sf::Font font;

public:
    Info();
    void draw(sf::RenderWindow& window) const;
    void setScope(unsigned scope);
    void fixScope();
    void setPos(sf::Vector2u pos);
};
