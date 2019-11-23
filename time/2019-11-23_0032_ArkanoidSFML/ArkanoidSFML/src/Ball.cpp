#include "Ball.h"
#include <iostream>
#include "HelperFunctions.h"

Ball::Ball()
{
    m_speed = { 0, -100 };
    m_radius = 10;
    m_drawShape = hf::createCircleShape(m_radius, state().getPos());
    m_collisionRect = hf::extractInsideRectShape(m_drawShape);
}

void Ball::onBumping(std::vector<Collision>& collisions)
{
    if(!collisions.empty())
        m_speed = { 0, 0 };
}

void Ball::calcState(sf::Event event, sf::Time elapsedTime)
{
    auto pos = state().getPos();
    sf::Vector2f offset = { elapsedTime.asSeconds() * m_speed.x, elapsedTime.asSeconds() * m_speed.y };
    auto newPos = pos + offset;
    state().setPos(newPos);

    m_drawShape.setPosition(newPos);
    m_collisionRect.setPosition(newPos);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(m_drawShape);
}
