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

inline BonusType getBonusTypeFromInt(int number)
{
    int size = static_cast<int>(BonusType::FireBall) + 1;
    int bonusNum = number % size;
    return static_cast<BonusType>(bonusNum);
}    

class IBonusOwner
{
public:
    virtual ~IBonusOwner() = default;
    virtual void setBonusType(std::optional<BonusType> bonusType) = 0;
    virtual std::optional<BonusType> getBonusType() = 0;
};