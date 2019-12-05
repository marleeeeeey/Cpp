#pragma once
#include "DefaultObject.h"
#include "IStaticObject.h"

class Wall : public DefaultObject, public IStaticObject
{
public:
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<IObject> createCopyFromThis() override;
};
