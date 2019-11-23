#pragma once
#include "DefaultObject.h"

class Wall : public DefaultObject
{
public:
    void draw(sf::RenderWindow& window) override;
};
