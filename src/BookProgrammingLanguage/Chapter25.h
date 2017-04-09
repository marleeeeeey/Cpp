#pragma once
#include "StdHelper.hpp"


namespace StProgLangChapter25
{
    class Window
    {
    public:
        virtual void draw() { AFUN; }
    };

    class Cowboy
    {
    public:
        virtual void draw() { AFUN; }
    };
    
    class CCowboy : public Cowboy
    {
    public:
        virtual void cow_draw() { AFUN; }
        void draw() { cow_draw(); }
    };

    class CWindow : public Window
    {
    public:
        virtual void win_draw() { AFUN; }
        void draw() { win_draw(); }
    };

    class Cowboy_Window : public CCowboy, public CWindow
    {
    public:
        void cow_draw() { AFUN; }
        void win_draw() { AFUN; }
    };

    static void resolve()
    {
        AFUN;
        Cowboy_Window cw;
        cw.cow_draw();
        cw.win_draw();

        CWindow cwin;
        cwin.draw();
        cwin.win_draw();

    }
}