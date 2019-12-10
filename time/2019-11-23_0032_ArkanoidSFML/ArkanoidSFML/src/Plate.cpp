#include "Plate.h"
#include "HelperFunctions.h"
#include "IStaticObject.h"
#include "IDynamicObject.h"
#include <iostream>

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
    else if(event && event.value().type == sf::Event::EventType::KeyReleased
        && event.value().key.code == sf::Keyboard::Key::Space
        && m_plateState != PlateState::Attack)
    {
        m_plateState = PlateState::Attack;
    }

    int speed_pxps = 600;
    float elapsedSec = elapsedTime.asSeconds();
    if (elapsedSec > 0.1)
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
    if(haveCollisions(m_collisionWalls))
    {
        m_offset = 0;
        restoreState();
    }
    else
    {
        saveState();
        m_collisionWalls.clear();
    }

    auto size = state().getSize();
    if (m_bonusType && m_bonusType.value() == BonusType::LongPlate)
    {
        if (!m_originalSize)
            m_originalSize = size;

        size = m_originalSize.value();
        size.x *= 1.5;
        state().setSize(size);
    }
    else
    {
        if (m_originalSize)
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
            m_collisionWalls.push_back(obj);
        }
        if (ball)
        {
            auto ballCenter = obj->state().getPos();
            auto plateCenter = state().getPos();
            auto centersShift = ballCenter.x - plateCenter.x;
            auto halfLength = state().getSize().x / 2;
            float maxAgnleShift = 10;
            float angleShift = maxAgnleShift * centersShift / halfLength;
            ball->speed().rotate(angleShift);
            if(m_bonusType && m_bonusType.value() == BonusType::MagnetPaddle && m_plateState != PlateState::Attack)
            {
                auto ballPos = obj->state().getPos();
                float plateLeft = state().getCollisionRect().getGlobalBounds().left;
                float plateRight = plateLeft + state().getCollisionRect().getGlobalBounds().width;
                if(ballPos.x < plateLeft)
                    ballPos.x = plateLeft;
                if(ballPos.x > plateRight)
                    ballPos.x = plateRight;
                obj->state().setPos(ballPos);
                ball->speed().setSize(0);
            }
        }
    }
}

std::optional<BonusType>& Plate::bonusType()
{
    return m_bonusType;
}

std::shared_ptr<IObject> Plate::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Plate>();
    Plate& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
}

std::string Plate::name()
{
    return "Plate";
}
