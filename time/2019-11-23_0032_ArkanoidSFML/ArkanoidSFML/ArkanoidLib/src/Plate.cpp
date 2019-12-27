#include "Plate.h"
#include "HelperFunctions.h"
#include "IStaticObject.h"
#include "IDynamicObject.h"
#include "IHaveParent.h"

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
    else if (event && event.value().type == sf::Event::EventType::KeyReleased
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
    sf::Vector2f pos01 = state().getPos();
    calculateOffset(event, elapsedTime);
    auto pos = state().getPos();
    pos.x += m_offset;
    state().setPos(pos);
    if (haveCollisions(m_collisionWalls))
    {
        m_offset = 0;
        restoreState();
    }
    else
    {
        saveState();
        m_collisionWalls.clear();
    }

    sf::Vector2f pos02 = state().getPos();
    sf::Vector2f shift = pos02 - pos01;

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

    for (auto ball : m_magnetBalls)
    {
        auto ballPos = ball->state().getPos();
        ballPos += shift;
        ball->state().setPos(ballPos);
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

float getShiftCoef(std::shared_ptr<IObject> plate, std::shared_ptr<IObject> obj)
{
    auto ballCenter = obj->state().getPos();
    auto plateCenter = plate->state().getPos();
    auto centersShift = ballCenter.x - plateCenter.x;
    auto halfLength = plate->state().getSize().x / 2;
    auto result = centersShift / halfLength;
    return result;
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
            m_collisionWalls.insert(obj);
        }
        if (ball)
        {
            float maxAgnleShift = 10;
            float angleShift = maxAgnleShift * getShiftCoef(shared_from_this(), obj);
            ball->speed().rotate(angleShift);
            if (m_bonusType && m_bonusType.value() == BonusType::MagnetPaddle && m_plateState != PlateState::Attack)
            {
                auto result = m_magnetBalls.insert(obj);
                if(result.second)
                {
                    auto ball = std::dynamic_pointer_cast<IHaveParent>(obj);
                    ball->setParent(shared_from_this());
                }
            }
            else
            {
                for(auto magnetBall : m_magnetBalls)
                {
                    auto childBall = std::dynamic_pointer_cast<IHaveParent>(magnetBall);
                    childBall->removeParent();
                    float maxAngle_deg = 45;
                    float angle = maxAngle_deg * getShiftCoef(shared_from_this(), magnetBall) - 90;
                    auto dynamicBall = std::dynamic_pointer_cast<IDynamicObject>(magnetBall);
                    dynamicBall->speed().setAngle(angle);
                }
                m_magnetBalls.clear();
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
