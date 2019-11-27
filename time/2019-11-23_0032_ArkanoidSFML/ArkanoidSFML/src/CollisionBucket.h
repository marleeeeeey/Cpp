#pragma once
#include <memory>
#include <functional>
#include "IObject.h"

class CollisionBucket
{
    std::vector<std::shared_ptr<IObject>>& m_primaryObjects;
    std::vector<std::shared_ptr<IObject>>& m_secondaryObjects;
    OnBumpingCallback m_onBumpingCallback;

public:
    CollisionBucket(std::vector<std::shared_ptr<IObject>>& primaryObjects,
                       std::vector<std::shared_ptr<IObject>>& secondaryObjects,
                       OnBumpingCallback cb);
    void process() const;
};
