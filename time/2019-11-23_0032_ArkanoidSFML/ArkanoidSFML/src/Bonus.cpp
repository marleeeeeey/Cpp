#include "Bonus.h"
#include "HelperFunctions.h"

Bonus::Bonus()
{
    m_font = hf::getDefaultFont();
}

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
    shape.setFillColor(hf::getAlphaColor(sf::Color::Yellow, 0x80));

    if (m_bonusType)
    {
        sf::Text text;
        text.setFont(m_font);
        text.setFillColor(sf::Color::Black);
        text.setString(hf::to_string(m_bonusType.value()));
        hf::setTextCenterTo(text, state().getPos());
        window.draw(shape);
        window.draw(text);
    }
    else
    {
        window.draw(shape);
    }
}

void Bonus::setBonusType(std::optional<BonusType> bonusType)
{
    m_bonusType = bonusType;
    if (m_bonusType)
    {
        auto oldSize = state().getSize();
        state().setSize({oldSize.x * 4, oldSize.y * 4});
    }
}

std::optional<BonusType> Bonus::getBonusType()
{
    return m_bonusType;
}

std::shared_ptr<IObject> Bonus::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Bonus>();
    Bonus& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
}
