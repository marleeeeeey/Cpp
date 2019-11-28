#pragma once
#include "DefaultObject.h"
#include "IBonusOwner.h"

class Bonus : public DefaultObject, public IBonusOwner
{
    std::optional<BonusType> m_bonusType;
    sf::Font m_font;

public:
    Bonus();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    void setBonusType(std::optional<BonusType> bonusType) override;
    std::optional<BonusType> getBonusType() override;
};
