#pragma once
#include "DefaultObject.h"

class Plate : public DefaultObject
{
    float m_speed;

public:
    Plate();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
