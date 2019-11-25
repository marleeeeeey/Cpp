#pragma once
#include "IObject.h"

class DefaultObject : public IObject
{
    State m_state;
    std::shared_ptr<IObjectFactory> m_objectFactory;
    std::function<void(std::vector<Collision> & collisions)> m_onBumpingCallback;

public:
    DefaultObject(std::shared_ptr<IObjectFactory> objectFactory);
    void checkBumping(std::vector<std::shared_ptr<IObject>>& objects) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setOnBumpingCallBack(std::function<void(std::vector<Collision> & collisions)> cb) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    State& state() override;
    std::optional<std::vector<std::shared_ptr<IObject>>> stealChildren() override;
    std::shared_ptr<IObjectFactory> getObjectFactory() override;
};
