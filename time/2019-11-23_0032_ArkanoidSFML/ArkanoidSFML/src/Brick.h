#pragma once
#include "DefaultObject.h"
#include "IDescructible.h"
#include "IBonusOwner.h"

class Brick : public DefaultObject, public IDescructible, public IBonusOwner
{
    std::optional<int> m_lives;
    int m_appearanceNumber;
    std::optional<BonusType> m_bonusType;

public:
    Brick();
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setLives(std::optional<int> lives) override;
    std::optional<int> getLives() override;
    void setAppearance(int appearanceNumber) override;
    void setBonusType(std::optional<BonusType> bonusType) override;
    std::optional<BonusType> getBonusType() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
};
