#pragma once

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

class IBonusOwner
{
public:
    virtual ~IBonusOwner() = default;
    virtual void setBonusType(BonusType bonusType) = 0;
    virtual BonusType getBonusType() = 0;
};