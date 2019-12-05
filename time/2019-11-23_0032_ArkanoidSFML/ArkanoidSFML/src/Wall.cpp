#include "Wall.h"

void Wall::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}

std::shared_ptr<IObject> Wall::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Wall>();
    Wall& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
}
