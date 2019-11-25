#pragma once
#include "DefaultObject.h"

class Plate : public DefaultObject
{
    float m_speed;
    std::optional<State> m_lastNonCollisionState;
    std::function<void(std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)> m_onBumpingCallBack;

public:
    Plate();
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setOnBumpingCallBack(std::function<void(std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)> cb) override;
};
