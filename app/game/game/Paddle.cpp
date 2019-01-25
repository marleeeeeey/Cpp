#include "stdafx.h"
#include "Paddle.h"
#include <optional>

Paddle::Paddle()
{
    paddleShape.setSize(paddleSize - sf::Vector2f(3, 3));
    paddleShape.setOutlineThickness(3);
    paddleShape.setOutlineColor(sf::Color::Black);
    paddleShape.setFillColor(sf::Color(100, 100, 200));
    paddleShape.setOrigin(paddleSize / 2.f);
}

void Paddle::setFillColor(const sf::Color& color)
{
    paddleShape.setFillColor(color);
}

void Paddle::setPosition(const float x, const float y)
{
    paddleShape.setPosition(x, y);
}

const sf::Vector2f& Paddle::getPosition() const
{
    return paddleShape.getPosition();
}

void Paddle::draw(sf::RenderWindow& window)
{
    correctPosition(window);
    window.draw(paddleShape);
}

void Paddle::move(const float offsetX, const float offsetY)
{
    paddleShape.move(offsetX, offsetY);
}

const sf::Vector2f& Paddle::getSize() const
{
    return paddleShape.getSize();
}

void Paddle::correctPosition(sf::RenderWindow& window)
{
    std::pair<float, float> verticalBounds{0 + paddleSize.x / 2, window.getSize().x - paddleSize.x / 2};
    std::pair<float, float> horizontalBounds{0 + paddleSize.y / 2, window.getSize().y - paddleSize.y / 2};

    std::optional<float> xPos;
    std::optional<float> yPos;

    if (paddleShape.getPosition().x > verticalBounds.second)
        xPos = std::make_optional(verticalBounds.second);
    else if (paddleShape.getPosition().x < verticalBounds.first)
        xPos = std::make_optional(verticalBounds.first);
    else if (paddleShape.getPosition().y > horizontalBounds.second)
        yPos = std::make_optional(horizontalBounds.second);
    else if (paddleShape.getPosition().y < horizontalBounds.first)
        yPos = std::make_optional(horizontalBounds.first);

    if (xPos.has_value())
        paddleShape.setPosition(xPos.value(), paddleShape.getPosition().y);

    if (yPos.has_value())
        paddleShape.setPosition(paddleShape.getPosition().x, yPos.value());
}
