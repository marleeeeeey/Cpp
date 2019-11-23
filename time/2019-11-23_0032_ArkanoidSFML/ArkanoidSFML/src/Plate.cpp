#include "Plate.h"
#include "HelperFunctions.h"

void Plate::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    float xSpeed = 0;

    if (event)
    {
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Left))
        {
            xSpeed = -2000;
        }
        if (hf::isKeyPressed(event.value(), sf::Keyboard::Right))
        {
            xSpeed = 2000;
        }
    }

    float offset = xSpeed * elapsedTime.asSeconds();
    auto pos = state().getPos();
    pos.x += offset;
    state().setPos(pos);
}

void Plate::draw(sf::RenderWindow& window)
{
    window.draw(state().getCollisionRect());
}
