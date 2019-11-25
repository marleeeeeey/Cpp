#pragma once
#include "Collision.h"
#include "IObject.h"

class CollisionProcessor
{
    std::vector<std::shared_ptr<IObject>>& m_primaryObjects;
    std::vector<std::shared_ptr<IObject>>& m_secondaryObjects;
    std::function<void(std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)> m_onBumpingCallback;

public:
    CollisionProcessor(std::vector<std::shared_ptr<IObject>>& primaryObjects,
                       std::vector<std::shared_ptr<IObject>>& secondaryObjects,
                       std::function<void(std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)> cb);
    void process();
};
