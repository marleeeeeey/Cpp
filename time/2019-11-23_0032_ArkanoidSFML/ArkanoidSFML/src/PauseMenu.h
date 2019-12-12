#pragma once
#include "DefaultObject.h"
#include "IObjectFactory.h"

class PauseMenu : public DefaultObject
{
    sf::Font m_font;
    bool m_isVisible;
    int m_elapsed_ms;

public:
    PauseMenu();
    std::string name() override;
    std::shared_ptr<IObject> createCopyFromThis() override;
    void draw(sf::RenderWindow& window) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    bool isVisible() override;
};
