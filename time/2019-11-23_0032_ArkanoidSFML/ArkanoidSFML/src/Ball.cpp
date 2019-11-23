#include "Ball.h"
#include <iostream>
#include "HelperFunctions.h"

Ball::Ball()
{
    m_speed = {0, -200};
}

void Ball::onBumping(std::vector<Collision>& collisions)
{
    //    if(!collisions.empty())
    //    {
    //        m_speed = { 0, 0 };
    //        std::cout << "ball has a collision" << std::endl;
    //    }

    // for (auto collision : collisions)
    // {
    //     collision.getObject()->state().setDestroyFlag(true);
    // }

    for (auto collision : collisions)
    {        
        std::vector<Collision> responseCollisions;
        responseCollisions.emplace_back(shared_from_this(), collision.getCollisionRect());
        collision.getObject()->onBumping(responseCollisions);
    }
}

void Ball::debugFunControlBall(std::optional<sf::Event> event)
{
    if (event)
    {
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Up))
        {
            m_speed = {0, -1000};
        }
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Down))
        {
            m_speed = {0, 1000};
        }
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Left))
        {
            m_speed = {-1000, 0};
        }
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Right))
        {
            m_speed = {1000, 0};
        }
    }
    else
    {
        m_speed = {0, 0};
    }
}

void Ball::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    //debugFunControlBall(event);

    auto pos = state().getPos();
    sf::Vector2f offset = {elapsedTime.asSeconds() * m_speed.x, elapsedTime.asSeconds() * m_speed.y};
    state().setPos(pos + offset);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(state().getCollisionRect());
}
