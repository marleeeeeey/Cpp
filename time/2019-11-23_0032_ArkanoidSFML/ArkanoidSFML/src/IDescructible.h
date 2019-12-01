#pragma once

class IDescructible
{
public:
    virtual ~IDescructible() = default;
    virtual void setLives(int lives) = 0;
    virtual void setAppearance(int appearanceNumber) = 0;
};
