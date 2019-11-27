#pragma once
#include "IObject.h"

class DefaultObject : public IObject
{
    State m_state;
    OnBumpingCallback m_onBumpingCallback;

public:
    void checkBumping(std::vector<std::shared_ptr<IObject>>& objects) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setOnBumpingCallBack(OnBumpingCallback cb) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    State& state() override;
};
