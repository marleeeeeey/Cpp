#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
    sf::RectangleShape paddleShape;
    sf::Vector2f paddleSize{ 25, 100 };

public:
    Paddle();
    void setFillColor(const sf::Color& color);
    void setPosition(float x, float y);
    const sf::Vector2f& getPosition() const;

    void draw(sf::RenderWindow& window);
    void move(float offsetX, float offsetY);
    const sf::Vector2f& getSize() const;

private:
    void correctPosition(sf::RenderWindow& window);
};

