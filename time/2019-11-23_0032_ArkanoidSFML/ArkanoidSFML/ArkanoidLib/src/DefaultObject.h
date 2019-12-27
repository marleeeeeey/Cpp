#pragma once
#include "IObject.h"
#include <set>

class DefaultObject : public IObject
{
    std::optional<State> m_savedState;
    State m_state;
    OnBumpingCallback m_onBumpingCallback;

protected:
    bool haveCollisions(std::set<std::shared_ptr<IObject>> objects);

public:
    void checkBumping(std::vector<std::shared_ptr<IObject>>& objects) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void setOnBumpingCallBack(OnBumpingCallback cb) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    State& state() override;
    void saveState() override;
    void restoreState() override;
    bool isVisible() override;
};
