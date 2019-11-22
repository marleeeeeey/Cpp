#pragma once
#include "DefaultObject.h"

class Wall : public DefaultObject
{
public:
    void calcState(sf::Event event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
