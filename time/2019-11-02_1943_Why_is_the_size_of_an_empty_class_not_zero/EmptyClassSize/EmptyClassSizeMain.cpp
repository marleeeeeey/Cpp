#include <iostream>

// To ensure that the addresses of two different objects will be different. 
// For the same reason, "new" always returns pointers to distinct objects. Consider:
class Empty { };

//  There is an interesting rule that says that an empty base class need not 
// be represented by a separate byte:

struct X : Empty {
    int a;
    // ...
};

// This optimization is safe and can be most useful. 
// It allows a programmer to use empty classes to represent very simple 
// concepts without overhead. 
// Some current compilers provide this "empty base class optimization".

void f(X* p)
{
    void* p1 = p;
    void* p2 = &p->a;
    if(p1 == p2) 
        std::cout << "nice: good optimizer\n";
}

void f()
{
    Empty a, b;
    if(&a == &b)
        std::cout << "impossible: report error to compiler supplier\n";
    else
        std::cout << "Empty a, b; &a != &b\n";
        
    std::cout << "sizeof(a)=" << sizeof(a) << " char\n";

    Empty* p1 = new Empty;
    Empty* p2 = new Empty;
    if(p1 == p2) 
        std::cout << "impossible: report error to compiler supplier\n";
    else
        std::cout << "Empty* p1 = new Empty; ... p1 != p2\n";

    std::cout << "sizeof(p1)=" << sizeof(p1) << " char\n";
}

int main()
{
    f();
    X x;
    f(&x);
}