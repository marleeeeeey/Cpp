#pragma once
#include "DefaultObject.h"
#include "IBonusOwner.h"

class Bonus : public DefaultObject, public IBonusOwner
{
    sf::Vector2f m_boundRectStandartSize;
    sf::Vector2f m_boundRectBonusSize;
    std::optional<BonusType> m_bonusType;
    sf::Font m_font;

public:
    Bonus();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    std::optional<BonusType>& bonusType() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
};
