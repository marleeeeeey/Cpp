#pragma once

#include "SpeakingClass.h"


namespace CtorVirtualTest
{
    class A
    {
    public:
        A()
        {
            AFUN;
            init();         // ¬ызываетс€ init базового класса
        }                   // ¬еро€тно, что в C# работает иначе!

        virtual ~A()        // virtual, чтобы корректно удал€ть 
        {                   // по указателю на базовый класс
            AFUN;
        }       

        virtual void init()
        {
            AFUN;
        }

    private:

        SpeakingClass sc;
    };

    class B : public A      // public наследование, чтобы 
    {                       // у клиентов производного класса был 
    public:                 // доступ к не€вному преобразованию 
        B()                 // указател€ на производный класс 
        {                   // в указатель на базовый класс. 
            AFUN;
        }

        ~B()
        {
            AFUN;
        }

        virtual void init()
        {
            AFUN;
        }

    private:

        SpeakingClass sc;
    };

    void resolve()
    {
        AFUN;
        A * a = new B();
        a->init();
        delete a;
    }
}

// SpeakingClass::SpeakingClass(int)
// CtorVirtualTest::A::A(void)
// void CtorVirtualTest::A::init(void)      // ¬ызываетс€ виртуальна€ фунци€ 
                                            // базового класса!!!
// SpeakingClass::SpeakingClass(int)        
// CtorVirtualTest::B::B(void)

// CtorVirtualTest::B::~B(void)
// SpeakingClass::~SpeakingClass(void)

// CtorVirtualTest::A::~A(void)
// SpeakingClass::~SpeakingClass(void)