#pragma once

class IDescructible
{
public:
    virtual ~IDescructible() = default;
    virtual void setLives(std::optional<int> lives) = 0;
    virtual std::optional<int> getLives() = 0;
    //TODO remove from this interface
    virtual void setAppearance(int appearanceNumber) = 0;
};
