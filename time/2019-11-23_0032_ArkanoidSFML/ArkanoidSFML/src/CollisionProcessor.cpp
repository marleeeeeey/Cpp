#include "CollisionProcessor.h"
#include "HelperFunctions.h"

CollisionProcessor::CollisionProcessor(std::vector<std::shared_ptr<IObject>>& primaryObjects,
                                       std::vector<std::shared_ptr<IObject>>& secondaryObjects,
                                       OnBumpingCallback cb)
    : m_primaryObjects(primaryObjects), m_secondaryObjects(secondaryObjects), m_onBumpingCallback(cb)
{
}

void CollisionProcessor::process() const
{
    for (auto primaryObject : m_primaryObjects)
    {
        if (m_onBumpingCallback)
            primaryObject->setOnBumpingCallBack(m_onBumpingCallback);
        primaryObject->checkBumping(m_secondaryObjects);
    }
}
