#include "PauseMenu.h"
#include "HelperFunctions.h"
#include <iostream>

PauseMenu::PauseMenu()
{
    m_font = hf::getDefaultFont();
    m_isVisible = false;
    m_elapsed_ms = 0;
}

std::string PauseMenu::name()
{
    return "PauseMenu";
}

std::shared_ptr<IObject> PauseMenu::createCopyFromThis()
{
    return shared_from_this();
}

void PauseMenu::draw(sf::RenderWindow& window)
{
    if(!m_isVisible)
        return;

    auto shape = state().getCollisionRect();
    shape.setFillColor(hf::getAlphaColor(sf::Color::Black, 0x80));
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(100);

    int blinkPeriod_ms = 2000;
    int counter = m_elapsed_ms % blinkPeriod_ms;
    if(counter > blinkPeriod_ms / 2)
        counter = blinkPeriod_ms - counter;
    float alpha = (float)counter * 2 / blinkPeriod_ms * 0xff;

    text.setFillColor(hf::getAlphaColor(sf::Color::White, alpha));
    text.setString(hf::to_string("Pause Menu"));
    hf::setTextCenterTo(text, state().getPos());
    window.draw(shape);
    window.draw(text);
}

void PauseMenu::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    m_elapsed_ms += elapsedTime.asMilliseconds();

    if(event && event.value().type == sf::Event::EventType::KeyPressed
        && event.value().key.code == sf::Keyboard::Key::P)
    {
        m_isVisible = !m_isVisible;
    }
}

bool PauseMenu::isVisible()
{
    return  m_isVisible;
}
