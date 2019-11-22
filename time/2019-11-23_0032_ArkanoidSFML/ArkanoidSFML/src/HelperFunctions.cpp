#include "HelperFunctions.h"

using namespace HelperFunctions;

bool HelperFunctions::isKeyPressed(sf::Event event, sf::Keyboard::Key key)
{
    return (event.type == sf::Event::EventType::KeyPressed
        && event.key.code == key);
}
