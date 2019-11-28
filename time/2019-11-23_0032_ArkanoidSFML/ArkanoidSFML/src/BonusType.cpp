#include "BonusType.h"
#include <map>

BonusType getBonusTypeFromInt(int number)
{
    int size = static_cast<int>(BonusType::FireBall) + 1;
    int bonusNum = number % size;
    return static_cast<BonusType>(bonusNum);
}

std::ostream& operator<<(std::ostream& os, const BonusType& type)
{
    const std::map<BonusType, std::string> bonusMap
    {
        {BonusType::RenewableBalls, "R"},
        {BonusType::MultiBalls, "M"},
        {BonusType::AddPlateLive, "A"},
        {BonusType::LongPlate, "L"},
        {BonusType::MagnetPaddle, "G"},
        {BonusType::DisableBonuses, "D"},
        {BonusType::AroundWall, "W"},
        {BonusType::NextLevel, "N"},
        {BonusType::DecreaseBallSpeed, "S"},
        {BonusType::FireBall, "F"},
    };

    os << bonusMap.at(type);
    return os;
}
