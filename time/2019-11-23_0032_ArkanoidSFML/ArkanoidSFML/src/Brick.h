#pragma once
#include "DefaultObject.h"
#include "IDestructible.h"
#include "IBonusOwner.h"

class Brick : public DefaultObject, public IDestructible, public IBonusOwner
{
    std::optional<int> m_lives;
    std::optional<BonusType> m_bonusType;

public:
    Brick();
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    std::optional<int>& lives() override;
    std::optional<BonusType>& bonusType() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
};
