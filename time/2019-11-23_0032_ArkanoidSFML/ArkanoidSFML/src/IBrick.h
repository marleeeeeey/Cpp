#pragma once

class IBrick
{
public:
    virtual ~IBrick() = default;
    virtual void setLives(int lives) = 0;
    virtual void setAppearance(int appearanceNumber) = 0;
};