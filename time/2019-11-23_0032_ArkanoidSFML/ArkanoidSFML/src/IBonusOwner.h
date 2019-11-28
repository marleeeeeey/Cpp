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
    virtual void setBonusType(std::optional<BonusType> bonusType) = 0;
    virtual std::optional<BonusType> getBonusType() = 0;
};