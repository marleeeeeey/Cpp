#pragma once
#include "DefaultObject.h"

class Brick : public DefaultObject
{
    std::optional<std::vector<std::shared_ptr<IObject>>> m_children;

public:
    Brick(std::shared_ptr<IObjectFactory> objectFactory);
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    std::optional<std::vector<std::shared_ptr<IObject>>> stealChildren() override;
};
