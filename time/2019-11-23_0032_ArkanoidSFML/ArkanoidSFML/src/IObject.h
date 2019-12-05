#pragma once
#include <optional>
#include <functional>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Collision.h"

using OnBumpingCallback = std::function<void(std::shared_ptr<IObject> thisObject,
                                             std::vector<Collision>& collisions)>;

class IObject : public std::enable_shared_from_this<IObject>
{
public:
    virtual ~IObject() = default;
    virtual void checkBumping(std::vector<std::shared_ptr<IObject>>& objects) = 0;
    virtual void onBumping(std::vector<Collision>& collisions) = 0;
    virtual void setOnBumpingCallBack(OnBumpingCallback callback) = 0;
    virtual void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual State& state() = 0;
    virtual std::shared_ptr<IObject> createCopyFromThis() = 0;
};
