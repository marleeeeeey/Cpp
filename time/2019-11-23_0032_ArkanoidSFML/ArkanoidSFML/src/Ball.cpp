#include "Ball.h"
#include <iostream>
#include "HelperFunctions.h"

Ball::Ball()
{
    m_speed = { 1, -2 };
    m_radius = 10;
    m_drawShape = hf::createCircleShape(m_radius, state().getPos());
    m_collisionRect = hf::extractInsideRectShape(m_drawShape);
}

void Ball::onBumping(std::vector<Collision>& collisions)
{
    std::cout << "Ball::onBumping()" << std::endl;
    m_speed = - m_speed;
}

void Ball::calcState(sf::Event event, sf::Time elapsedTime)
{
    std::cout << "Ball::calcState()" << std::endl;
    auto pos = state().getPos();
    sf::Vector2f offset = { elapsedTime.asSeconds() * m_speed.x, elapsedTime.asSeconds() * m_speed.y };
    state().setPos(pos + offset);

    m_drawShape.setPosition(state().getPos());
    m_collisionRect.setPosition(state().getPos());
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(m_drawShape);
}
