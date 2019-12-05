#pragma once
#include "BonusType.h"

class IBonusOwner
{
public:
    virtual ~IBonusOwner() = default;
    virtual std::optional<BonusType>& bonusType() = 0;
};
