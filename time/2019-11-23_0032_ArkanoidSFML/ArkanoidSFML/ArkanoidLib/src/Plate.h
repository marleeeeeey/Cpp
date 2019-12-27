#pragma once
#include "DefaultObject.h"
#include "IBonusOwner.h"
#include "IDestructible.h"
#include <set>

enum class PlateState
{
    Stop,
    MoveLeft,
    MoveRight,
    Attack,
};

class Plate : public DefaultObject, public IBonusOwner
{
    std::optional<sf::Vector2f> m_originalSize;
    std::set<std::shared_ptr<IObject>> m_collisionWalls;
    std::set<std::shared_ptr<IObject>> m_magnetBalls;
    float m_offset;
    PlateState m_plateState;
    std::optional<BonusType> m_bonusType;

    void calculateOffset(std::optional<sf::Event> event, sf::Time elapsedTime);

public:
    Plate();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    std::optional<BonusType>& bonusType() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
    std::string name() override;
};
