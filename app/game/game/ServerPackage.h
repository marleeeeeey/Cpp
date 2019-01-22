#pragma once
#include <SFML/System/Vector2.hpp>

struct ServerPackage
{
    sf::Vector2i screenSize;
    sf::Vector2f leftPaddleCenter;
    sf::Vector2f leftPaddleSize;
    sf::Vector2f rightPaddleCenter;
    sf::Vector2f rightPaddleSize;
    sf::Vector2f ballCenter;
    float ballRadius;
    float paddleSpeed;
    float ballSpeed;
};
