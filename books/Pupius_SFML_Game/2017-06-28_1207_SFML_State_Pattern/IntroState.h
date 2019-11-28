#pragma once

class State_Intro : public BaseState 
{
public:
    void Continue(EventDetails* l_details);

private:
    sf::Texture m_introTexture;
    sf::Sprite  m_introSprite;
    sf::Text    m_text;
    float       m_timePassed;
};

