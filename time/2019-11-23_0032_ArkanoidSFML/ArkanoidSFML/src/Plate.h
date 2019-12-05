#pragma once
#include "DefaultObject.h"
#include "IBonusOwner.h"

enum class PlateState
{
    Stop,
    MoveLeft,
    MoveRight,
};

class Plate : public DefaultObject, public IBonusOwner
{
    std::optional<sf::Vector2f> m_originalSize;
    float m_offset;
    std::optional<State> m_lastNonCollisionState;
    PlateState m_plateState;
    std::optional<BonusType> m_bonusType;

    void calculateOffset(std::optional<sf::Event> event, sf::Time elapsedTime);

public:
    Plate();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setBonusType(std::optional<BonusType> bonusType) override;
    std::optional<BonusType> getBonusType() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
};
