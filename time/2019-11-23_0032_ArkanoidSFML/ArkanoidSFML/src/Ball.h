#pragma once
#include "DefaultObject.h"
#include "MathVector.h"
#include "IDynamicObject.h"
#include "IBonusOwner.h"

class Ball : public DefaultObject, public IDynamicObject, public IBonusOwner
{
    MathVector m_speed;
    float m_bonusSpeed = 200;
    float m_maxSpeed = 400;
    std::optional<Collision> m_biggestCollision;
    std::optional<State> m_lastNonCollisionState;
    std::optional<BonusType> m_bonusType;

    void changeDirection();
    void stealLiveFromOneDestructibleObject(std::vector<Collision>& collisions);

public:
    Ball();
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    MathVector& speed() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
    std::optional<BonusType>& bonusType() override;
};
