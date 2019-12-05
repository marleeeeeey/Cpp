#pragma once
#include "BonusType.h"

class IBonusOwner
{
public:
    virtual ~IBonusOwner() = default;
    virtual void setBonusType(std::optional<BonusType> bonusType) = 0;
    virtual std::optional<BonusType> getBonusType() = 0;
};
