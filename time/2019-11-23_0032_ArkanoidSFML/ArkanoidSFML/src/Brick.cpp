#include "Brick.h"
#include "HelperFunctions.h"
#include "IObjectFactory.h"

Brick::Brick(std::shared_ptr<IObjectFactory> objectFactory)
    : DefaultObject(objectFactory)
{
}

void Brick::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}

void Brick::onBumping(std::vector<Collision>& collisions)
{
    state().setDestroyFlag(true);
    auto objectFacory = getObjectFactory();
    auto bonus = objectFacory->createObject(ObjectType::Bonus);
    bonus->state().setSize({ 5, 5 });
    bonus->state().setPos(state().getPos());
    if(!m_children)
        m_children = std::vector<std::shared_ptr<IObject>>();
    m_children.value().push_back(bonus);
}

std::optional<std::vector<std::shared_ptr<IObject>>> Brick::stealChildren()
{
    auto temp = m_children;
    m_children.reset();
    return temp;
}
