#include "Bonus.h"


void Bonus::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    sf::Vector2f speed = {0, 100};

    auto pos = state().getPos();
    sf::Vector2f offset = {elapsedTime.asSeconds() * speed.x, elapsedTime.asSeconds() * speed.y};
    state().setPos(pos + offset);
}

void Bonus::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Yellow);
    window.draw(shape);
}

void Bonus::setBonusType(std::optional<BonusType> bonusType)
{
    m_bonusType = bonusType;
}

std::optional<BonusType> Bonus::getBonusType()
{
    return  m_bonusType;
}
