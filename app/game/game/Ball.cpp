#include "stdafx.h"
#include "Ball.h"

Ball::Ball()
{
    ballShape.setRadius(ballRadius - 3);
    ballShape.setOutlineThickness(3);
    ballShape.setOutlineColor(sf::Color::Black);
    ballShape.setFillColor(sf::Color::White);
    ballShape.setOrigin(ballRadius / 2, ballRadius / 2);
}

void Ball::setPosition(const float x, const float y)
{
    ballShape.setPosition(x, y);
}

const sf::Vector2f& Ball::getPosition() const
{
    return ballShape.getPosition();
}

void Ball::move(const float offsetX, const float offsetY)
{
    ballShape.move(offsetX, offsetY);
}

void Ball::changeRandomColor()
{
    const sf::Color newColor(std::rand() % 0xff, std::rand() % 0xff, std::rand() % 0xff);
    ballShape.setFillColor(newColor);
}

void Ball::draw(sf::RenderWindow& window) const
{
    window.draw(ballShape);
}

float Ball::getRadius() const
{
    return ballShape.getRadius();
}

void Ball::setSoundBuffer(const sf::SoundBuffer& ballSoundBuffer)
{
    ballSound.setBuffer(ballSoundBuffer);
}

void Ball::playSound()
{
    ballSound.play();
}
