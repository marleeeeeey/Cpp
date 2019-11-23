#include "Brick.h"
#include "HelperFunctions.h"

void Brick::draw(sf::RenderWindow& window)
{
    window.draw(state().getCollisionRect());
}

void Brick::onBumping(std::vector<Collision>& collisions)
{
}

void Brick::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    state().setCollisionRect(hf::createRectangleShape(state().getSize(), state().getPos()));
}
