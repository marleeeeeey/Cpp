#pragma once
#include "DefaultObject.h"

class Wall : public DefaultObject
{
public:
    Wall(std::shared_ptr<IObjectFactory> objectFactory);
    void draw(sf::RenderWindow& window) override;
};
