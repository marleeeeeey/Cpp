#pragma once
#include "Matrix.h"
#include "Object.h"

class Game
{
    Matrix m_matrix;
    Object m_object;
    Object m_nextObject;
    sf::Time m_lastTimeStamp;
    sf::Vector2u m_specialPos;

    Game(sf::Vector2u size);
    void draw(sf::RenderWindow& window, sf::Time time);
    void dispatchKey(sf::Event key);
};
