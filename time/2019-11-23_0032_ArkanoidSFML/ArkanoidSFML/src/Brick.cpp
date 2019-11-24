#include "Brick.h"
#include "HelperFunctions.h"

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
}
