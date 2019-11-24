#pragma once
#include "IObject.h"

class DefaultObject : public IObject
{
    State m_state;
    std::shared_ptr<IObjectFactory> m_objectFactory;

public:
    DefaultObject(std::shared_ptr<IObjectFactory> objectFactory);
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    State& state() override;
    std::optional<std::vector<std::shared_ptr<IObject>>> stealChildren() override;
    std::shared_ptr<IObjectFactory> getObjectFactory() override;
};
