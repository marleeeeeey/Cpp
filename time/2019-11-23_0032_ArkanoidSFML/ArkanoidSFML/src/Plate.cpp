#include "Plate.h"
#include "HelperFunctions.h"

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
