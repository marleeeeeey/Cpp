#include "Plate.h"
#include "HelperFunctions.h"
#include "Wall.h"
#include "Bonus.h"

Plate::Plate()
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

        // TODO
        auto bonus = std::dynamic_pointer_cast<Bonus>(obj);
        if (bonus)
        {
            bonus->state().setDestroyFlag(true);
        }
    }

    if (!isSpeedUpdated)
    {
        m_lastNonCollisionState = state();
    }
}

void Plate::setOnBumpingCallBack(std::function<void(std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)> cb)
{
    m_onBumpingCallBack = cb;
}
