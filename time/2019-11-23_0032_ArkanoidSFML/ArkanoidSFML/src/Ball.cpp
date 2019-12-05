#include "Ball.h"
#include "HelperFunctions.h"
#include "IDestructible.h"
#include "IStaticObject.h"

Ball::Ball()
{
    m_speed = MathVector(-33, 300);
    DefaultObject::state().setSize({20, 20});
}

float getArea(const sf::Vector2f& size)
{
    return size.x * size.y;
}

Collision getBiggestCollision(std::vector<Collision>& collisions)
{
    std::sort(collisions.begin(), collisions.end(), [](Collision& lhs, Collision& rhs)
    {
        auto areaLhs = getArea(lhs.getCollisionRect().getSize());
        auto areaRhs = getArea(rhs.getCollisionRect().getSize());
        return areaLhs < areaRhs;
    });

    return collisions.back();
}

void Ball::changeDirection()
{
    auto cs = m_biggestCollision.value().getCollisionRect().getSize();

    if (hf::isEqual(cs.x, cs.y))
    {
        m_speed.rotate(180);
    }
    else if (cs.x > cs.y)
    {
        m_speed.reflectFromHorizontal();
    }
    else
    {
        m_speed.reflectFromVertical();
    };
}

void Ball::stealLiveFromOneDestructibleObject(std::vector<Collision>& collisions)
{
    std::vector<std::shared_ptr<IDestructible>> desctructibleObjects;
    for (auto collision : collisions)
    {
        auto desctructible = std::dynamic_pointer_cast<IDestructible>(collision.getObject());
        if (desctructible)
        {
            desctructibleObjects.push_back(desctructible);
        }
    }

    if (!desctructibleObjects.empty())
    {
        auto& biggestObjectLives = desctructibleObjects.front()->lives();
        if (biggestObjectLives)
            biggestObjectLives.value()--;
    }
}

void Ball::onBumping(std::vector<Collision>& collisions)
{
    if (!collisions.empty())
    {
        m_biggestCollision = getBiggestCollision(collisions);

        if (m_bonusType && m_bonusType.value() == BonusType::FireBall)
        {
            auto collision = m_biggestCollision.value();
            auto collisionObject = collision.getObject();
            auto desctuctibleObject = std::dynamic_pointer_cast<IDestructible>(collisionObject);
            if (desctuctibleObject && desctuctibleObject->lives())
            {
                // do nothing
            }
            else
            {
                changeDirection();
            }
        }
        else
        {
            changeDirection();
        }

        if (m_lastNonCollisionState)
            state() = m_lastNonCollisionState.value();
    }
    else
    {
        m_lastNonCollisionState = state();
    }

    stealLiveFromOneDestructibleObject(collisions);

    for (auto collision : collisions)
    {
        std::vector<Collision> oneBackCollision;
        oneBackCollision.emplace_back(shared_from_this(), collision.getCollisionRect());
        collision.getObject()->onBumping(oneBackCollision);
    }
}

void Ball::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    auto sec = elapsedTime.asSeconds();

    float accelerate_pxps = 5;
    float speedShift = accelerate_pxps * sec;
    float speed = m_speed.getSize() + speedShift;
    if (speed > m_maxSpeed)
        speed = m_maxSpeed;
    m_speed.setSize(speed);

    if (m_bonusType && m_bonusType.value() == BonusType::DecreaseBallSpeed)
    {
        m_bonusType = {};
        m_speed.setSize(m_bonusSpeed);
    }

    auto pos = state().getPos();
    auto coordinates = m_speed.getCoordinate();
    sf::Vector2f offset = {sec * coordinates.x, sec * coordinates.y};
    state().setPos(pos + offset);
}

void Ball::draw(sf::RenderWindow& window)
{
    float rectSide = state().getCollisionRect().getSize().x;
    float radius = rectSide / sqrt(2);
    auto circleShape = hf::createCircleShape(radius, state().getPos());

    sf::Color shapeColor;
    if (m_bonusType && m_bonusType.value() == BonusType::FireBall)
    {
        shapeColor = sf::Color::Red;
    }
    else
    {
        shapeColor = sf::Color::Blue;
    }

    circleShape.setFillColor(shapeColor);
    window.draw(circleShape);
}

MathVector& Ball::speed()
{
    return m_speed;
}

std::shared_ptr<IObject> Ball::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Ball>();
    Ball& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
}

std::optional<BonusType>& Ball::bonusType()
{
    return m_bonusType;
}
