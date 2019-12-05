#pragma once

class IDestructible
{
public:
    virtual ~IDestructible() = default;
    virtual std::optional<int>& lives() = 0;
};
