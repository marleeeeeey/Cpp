#pragma once
#include "DefaultObject.h"

class Wall : public DefaultObject
{
public:
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
