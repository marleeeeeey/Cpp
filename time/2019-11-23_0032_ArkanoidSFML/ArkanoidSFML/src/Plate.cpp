#include "Plate.h"
#include "HelperFunctions.h"
#include "Wall.h"

Plate::Plate()
{
    m_offset = 0;
    m_plateState = PlateState::Stop;
}

void Plate::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    if (event && event.value().type == sf::Event::EventType::KeyPressed
        && event.value().key.code == sf::Keyboard::Key::Left
        && m_plateState != PlateState::MoveLeft)
    {
        m_plateState = PlateState::MoveLeft;
    }
    else if (event && event.value().type == sf::Event::EventType::KeyReleased
        && event.value().key.code == sf::Keyboard::Key::Left
        && m_plateState == PlateState::MoveLeft)
    {
        m_plateState = PlateState::Stop;
    }
    else if (event && event.value().type == sf::Event::EventType::KeyPressed
        && event.value().key.code == sf::Keyboard::Key::Right
        && m_plateState != PlateState::MoveRight)
    {
        m_plateState = PlateState::MoveRight;
    }
    else if (event && event.value().type == sf::Event::EventType::KeyReleased
        && event.value().key.code == sf::Keyboard::Key::Right
        && m_plateState == PlateState::MoveRight)
    {
        m_plateState = PlateState::Stop;
    }

    int speed_pxps = 600;
    float absOffset = speed_pxps * elapsedTime.asSeconds();
    float absDampingOffset = absOffset * 0.03f;

    switch (m_plateState)
    {
    case PlateState::Stop:
        if (m_offset > 0)
            m_offset -= absDampingOffset;
        else if (m_offset < 0)
            m_offset += absDampingOffset;
        if (m_offset != 0 && abs(m_offset) < absDampingOffset)
            m_offset = 0;
        break;
    case PlateState::MoveLeft:
        m_offset = -absOffset;
        break;
    case PlateState::MoveRight:
        m_offset = absOffset;
        break;
    }

    auto pos = state().getPos();
    pos.x += m_offset;
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
    for (auto collision : collisions)
    {
        auto obj = collision.getObject();
        auto wall = std::dynamic_pointer_cast<Wall>(obj);
        if (wall)
        {
            if (m_lastNonCollisionState)
                state() = m_lastNonCollisionState.value();

            m_offset = 0;
            return;
        }
    }

    m_lastNonCollisionState = state();
}
