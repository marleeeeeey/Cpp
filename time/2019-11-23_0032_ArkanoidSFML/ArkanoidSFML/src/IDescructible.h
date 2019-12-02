#pragma once

class IDescructible
{
public:
    virtual ~IDescructible() = default;
    virtual void setLives(int lives) = 0;
    //TODO remove from this interface
    virtual void setAppearance(int appearanceNumber) = 0;
};
