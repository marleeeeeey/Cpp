#pragma once


#include <SFML/Graphics.hpp>
#include "Window.h"

class Game
{
public:
    Game();
    ~Game();
    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
private:
    void MoveMushroom();

    Window  m_window;
    Snake   m_snake;
    World   m_world;
    Textbox m_textbox;
};

