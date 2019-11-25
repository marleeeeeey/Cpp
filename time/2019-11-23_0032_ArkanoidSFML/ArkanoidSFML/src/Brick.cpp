#include "Brick.h"
#include "HelperFunctions.h"
#include "IObjectFactory.h"

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
