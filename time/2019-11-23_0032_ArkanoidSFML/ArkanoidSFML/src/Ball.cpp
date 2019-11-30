#include "Ball.h"
#include "HelperFunctions.h"

Ball::Ball()
{
    m_speed = MathVector(-33, 300);
    DefaultObject::state().setSize({ 20, 20 });
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

void Ball::onBumping(std::vector<Collision>& collisions)
{
    if (!collisions.empty())
    {
        m_biggestCollision = getBiggestCollision(collisions);
        auto cs = m_biggestCollision.value().getCollisionRect().getSize();

        if (hf::isEqual(cs.x , cs.y))
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

        if (m_lastNonCollisionState)
            state() = m_lastNonCollisionState.value();
    }
    else
    {
        m_lastNonCollisionState = state();
    }

    for (auto collision : collisions)
    {
        std::vector<Collision> responseCollisions;
        responseCollisions.emplace_back(shared_from_this(), collision.getCollisionRect());
        collision.getObject()->onBumping(responseCollisions);
    }
}

void Ball::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    auto pos = state().getPos();
    auto coordinates = m_speed.getCoordinates();
    sf::Vector2f offset = {elapsedTime.asSeconds() * coordinates.x, elapsedTime.asSeconds() * coordinates.y};
    state().setPos(pos + offset);
}

void Ball::draw(sf::RenderWindow& window)
{
    float rectSide = state().getCollisionRect().getSize().x;
    float radius = rectSide / sqrt(2);
    auto circleShape = hf::createCircleShape(radius, state().getPos());
    circleShape.setFillColor(sf::Color::Blue);
    window.draw(circleShape);
}
