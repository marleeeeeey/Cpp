#pragma once
#include "DefaultObject.h"
#include "IBrick.h"
#include "IBonusOwner.h"

class Brick : public DefaultObject, IBrick, IBonusOwner
{
    int m_lives;
    int m_appearanceNumber;
    std::optional<BonusType> m_bonusType;

public:
    Brick();
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setLives(int lives) override;
    void setAppearance(int appearanceNumber) override;
    void setBonusType(std::optional<BonusType> bonusType) override;
    std::optional<BonusType> getBonusType() override;
};
