#include "Plate.h"
#include "HelperFunctions.h"
#include "Wall.h"
#include "Bonus.h"

Plate::Plate(std::shared_ptr<IObjectFactory> objectFactory)
    : DefaultObject(objectFactory)
{
    m_speed = 0;
}

void Plate::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    float koef = 10;

    if (event)
    {
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Left))
        {
            m_speed = -koef;
        }
        else if (hf::isKeyPressed(event.value(), sf::Keyboard::Right))
        {
            m_speed = koef;
        }
    }
    else
    {
        m_speed *= 0.9;
        if (abs(m_speed) < koef / 10)
            m_speed = 0;
    }

    float offset = m_speed;
    auto pos = state().getPos();
    pos.x += offset;
    state().setPos(pos);
}

void Plate::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Cyan);
    window.draw(shape);
}

void Plate::onBumping(std::vector<Collision>& collisions)
{
    std::vector<Collision> bonusCollisions;
    bool isSpeedUpdated = false;

    for (auto collision : collisions)
    {
        auto obj = collision.getObject();
        auto wall = std::dynamic_pointer_cast<Wall>(obj);
        if (wall && !isSpeedUpdated)
        {
            if (m_lastNonCollisionState)
                state() = m_lastNonCollisionState.value();

            m_speed = 0;
            isSpeedUpdated = true;
        }

        auto bonus = std::dynamic_pointer_cast<Bonus>(obj);
        if (bonus)
        {
            bonusCollisions.push_back(collision);
            bonus->state().setDestroyFlag(true);
        }
    }

    if (!isSpeedUpdated)
    {
        m_lastNonCollisionState = state();
    }
    if (!bonusCollisions.empty())
    {
        m_onBumpingCallBack(bonusCollisions);
    }
}

void Plate::setOnBumpingCallBack(std::function<void(std::vector<Collision>& collisions)> cb)
{
    m_onBumpingCallBack = cb;
}
