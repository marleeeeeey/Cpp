#pragma once

#include "Lines.hpp"

class Object
{
    Lines m_shape;
    sf::Vector2u m_pos;

public:
    Object();
    Object(const Object& other);
    Object getMoved(int x, int y) const;
    void generateShape(); 
    void draw(sf::RenderWindow& window) const;
    void setShape(const Lines& shape);
    const Lines& getShape() const;
    void setPos(sf::Vector2u pos);
    sf::Vector2u getPos() const;
    bool isVisible(sf::Vector2u matrixPos) const;
    Cell getCell(sf::Vector2u matrixPos) const;
    Object getRotateObject() const;
    sf::Vector2u getBoundSize() const;
};