#include "Wall.h"

void Wall::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}
