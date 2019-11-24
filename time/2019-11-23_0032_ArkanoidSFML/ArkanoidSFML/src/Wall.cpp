#include "Wall.h"

Wall::Wall(std::shared_ptr<IObjectFactory> objectFactory)
    : DefaultObject(objectFactory)
{
}

void Wall::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}
