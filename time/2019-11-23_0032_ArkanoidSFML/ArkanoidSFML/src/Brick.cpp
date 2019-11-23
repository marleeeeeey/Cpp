#include "Brick.h"
#include "HelperFunctions.h"

void Brick::draw(sf::RenderWindow& window)
{
    auto rectShape = hf::createRectangleShape(state().getSize(), state().getPos());
    window.draw(rectShape);
}
