#pragma once
#include "Matrix.h"
#include "Object.h"
#include "Info.h"

bool isKeyPressed(sf::Event event, sf::Keyboard::Key key);

class Game
{
    Matrix m_matrix;
    Object m_object;
    Object m_nextObject;
    sf::Time m_lastTimeStemp;
    sf::Clock clock; // starts the clock
    bool m_isAccelerate;
    Info m_info;
    bool m_isPause;

public:
    Game(sf::Vector2u size);
    void draw(sf::RenderWindow& window);
    void dispatchKey(sf::Event key);
    void onGameOver();
};
