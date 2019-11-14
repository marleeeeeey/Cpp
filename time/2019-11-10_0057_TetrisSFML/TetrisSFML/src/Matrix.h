#pragma once
#include <SFML/System/Vector2.hpp>
#include "Lines.hpp"
#include "Object.h"

class Matrix
{
    sf::Vector2u m_size;
    Lines m_cellTable;
    unsigned m_removedLineCounter;

public:
    Matrix(sf::Vector2u size);
    void add(const Object& object);
    bool checkCollision(const Object& object);
    void draw(sf::RenderWindow& window);
    void clear();
    unsigned getRemovedLineCounter();

private:
    void removeFullLines();
    void makeBorders();
};
