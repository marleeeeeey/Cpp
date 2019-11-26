#pragma once
#include "DefaultObject.h"

enum class PlateState
{
    Stop,
    MoveLeft,
    MoveRight,
};

class Plate : public DefaultObject
{
    float m_offset;
    std::optional<State> m_lastNonCollisionState;
    PlateState m_plateState;

public:
    Plate();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
};
