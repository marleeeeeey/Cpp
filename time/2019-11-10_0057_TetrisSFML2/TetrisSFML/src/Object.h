#pragma once

#include "Lines.hpp"

class Object
{
    Lines m_shape;
    sf::Vector2u m_pos;

public:
    Object();
    Object(const Object& other);
    Object getMoved(int x, int y);
    void generateShape(); // TODO move to Game class
    void draw(sf::RenderWindow& window);
    void setShape(const Lines& shape);
    const Lines& getShape();
    void setPos(sf::Vector2u pos);
    sf::Vector2u getPos();
};