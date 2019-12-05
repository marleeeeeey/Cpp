#pragma once

class IDestructible
{
public:
    virtual ~IDestructible() = default;
    virtual std::optional<int>& lives() = 0;
    //TODO remove from this interface
    virtual void setAppearance(int appearanceNumber) = 0;
};
