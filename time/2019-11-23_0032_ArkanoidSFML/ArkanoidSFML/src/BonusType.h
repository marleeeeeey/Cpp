#pragma once
#include <ostream>

enum class BonusType
{
    RenewableBalls,
    MultiBalls,
    AddPlateLive,
    LongPlate,
    MagnetPaddle,
    DisableBonuses,
    AroundWall,
    NextLevel,
    DecreaseBallSpeed,
    FireBall,
};

BonusType getBonusTypeFromInt(int number);

std::ostream& operator<<(std::ostream& os, const BonusType& type);
