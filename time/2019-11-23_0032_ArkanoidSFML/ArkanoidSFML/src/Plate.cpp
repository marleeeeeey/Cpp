#include "Plate.h"
#include "HelperFunctions.h"
#include "IStaticObject.h"
#include "IDynamicObject.h"

Plate::Plate()
{
    m_offset = 0;
    m_plateState = PlateState::Stop;
}

void Plate::calculateOffset(std::optional<sf::Event> event, sf::Time elapsedTime)
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
    float elapsedSec = elapsedTime.asSeconds();
    if(elapsedSec > 0.1)
        elapsedSec = 0.1;
    float absOffset = speed_pxps * elapsedSec;
    float absDampingOffset = absOffset * 0.08f;

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
}

void Plate::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    calculateOffset(event, elapsedTime);
    auto pos = state().getPos();
    pos.x += m_offset;
    state().setPos(pos);

    auto size = state().getSize();
    if(m_bonusType && m_bonusType.value() == BonusType::LongPlate)
    {
        if(!m_originalSize)
            m_originalSize = size;

        size = m_originalSize.value();
        size.x *= 1.5;
        state().setSize(size);
    }
    else
    {
        if(m_originalSize)
            state().setSize(m_originalSize.value());
    }
}

void Plate::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Cyan);
    window.draw(shape);

    if (m_bonusType)
    {
        sf::Text text;
        sf::Font font = hf::getDefaultFont();
        text.setFont(font);
        text.setString(hf::to_string(m_bonusType.value()));
        text.setFillColor(sf::Color::Blue);
        hf::setTextCenterTo(text, state().getPos());
        window.draw(text);
    }
}

void Plate::onBumping(std::vector<Collision>& collisions)
{
    for (auto collision : collisions)
    {
        auto obj = collision.getObject();
        auto wall = std::dynamic_pointer_cast<IStaticObject>(obj);
        auto ball = std::dynamic_pointer_cast<IDynamicObject>(obj);
        if (wall)
        {
            if (m_lastNonCollisionState)
                state() = m_lastNonCollisionState.value();

            m_offset = 0;
        }
        else if (ball)
        {
            auto ballSpeed = ball->getSpeed();
            auto ballCenter = obj->state().getPos();
            auto plateCenter = state().getPos();
            auto centersShift = ballCenter.x - plateCenter.x;
            auto halfLength = state().getSize().x / 2;
            float maxAgnleShift = 10;
            float angleShift = maxAgnleShift * centersShift / halfLength;
            ballSpeed.rotate(angleShift);
            ball->setSpeed(ballSpeed);
        }
    }

    m_lastNonCollisionState = state();
}

void Plate::setBonusType(std::optional<BonusType> bonusType)
{
    m_bonusType = bonusType;
}

std::optional<BonusType> Plate::getBonusType()
{
    return m_bonusType;
}
