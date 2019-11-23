#include "Ball.h"
#include <iostream>
#include "HelperFunctions.h"

Ball::Ball()
{
    m_speed = { 0, -200 };
    m_radius = 10;
}

void Ball::onBumping(std::vector<Collision>& collisions)
{
    if(!collisions.empty())
    {
        m_speed = { 0, 0 };
        std::cout << "ball has a collision" << std::endl;
    }
}

void Ball::debugFunControlBall(std::optional<sf::Event> event)
{
    if(event)
    {
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Up))
        {
            m_speed = { 0, -1000 };
        }
        if(hf::isKeyPressed(event.value(), sf::Keyboard::Down))
        {
            m_speed = { 0, 1000 };
        }
        if(hf::isKeyPressed(event.value(), sf::Keyboard::Left))
        {
            m_speed = { -1000, 0 };
        }
        if(hf::isKeyPressed(event.value(), sf::Keyboard::Right))
        {
            m_speed = { 1000, 0 };
        }
    }
    else
    {
        m_speed = { 0, 0 };
    }
}

void Ball::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{

    //debugFunControlBall(event);

    auto pos = state().getPos();
    sf::Vector2f offset = { elapsedTime.asSeconds() * m_speed.x, elapsedTime.asSeconds() * m_speed.y };
    auto newPos = pos + offset;
    auto drawShape = hf::createCircleShape(m_radius, newPos);
    auto collisionRect = hf::extractInsideRectShape(drawShape);

    state().setPos(newPos);
    state().setCollisionRect(collisionRect);
}

void Ball::draw(sf::RenderWindow& window)
{
    auto drawShape = hf::createCircleShape(m_radius, state().getPos());
    auto collisionRect = hf::extractInsideRectShape(drawShape);

    window.draw(collisionRect);
    window.draw(drawShape);
}
