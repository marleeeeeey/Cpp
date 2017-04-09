#pragma once

namespace DefineLinePointer
{
    struct Test
    {
        char a;
        char b;
        char c;
        char d;
        char e;
        char f;
        char g;
        char h;
    };



    void resolve()
    {
        AFUN;

        Test t;
        Test * pTest;

        AVAR(sizeof(Test));
        AVAR(sizeof(t));
        AVAR(sizeof(t.a));
        AVAR(sizeof(pTest));
        
        Test *p1, *p2, *p3; // Три указателя. ЗВЕЗДОЧКА относится к объекту, но не к типу!

//         AVAR(sizeof(p1));
//         AVAR(sizeof(p2));
//         AVAR(sizeof(p3));

        Test *p4, p5, p6; // Указатель + Объект + Объект. ЗВЕЗДОЧКА относится к объекту, но не к типу!

        AVAR(sizeof(p4));
        AVAR(sizeof(p5));
        AVAR(sizeof(p6));
    }
}


