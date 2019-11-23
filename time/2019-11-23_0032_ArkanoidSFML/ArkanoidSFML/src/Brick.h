#pragma once
#include "DefaultObject.h"

class Brick : public DefaultObject
{
public:
    void draw(sf::RenderWindow& window) override;
};
