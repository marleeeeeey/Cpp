#include <string>
#include <memory>
#include <vector>
#include <iostream>

class Person
{
public:
    static int counterOfAlivePerson;
    std::string name;
    std::shared_ptr<Person> mother;
    std::shared_ptr<Person> father;
    std::vector<std::weak_ptr<Person>> kids; // weak pointer !!!

    Person(const std::string& n,
           std::shared_ptr<Person> m = nullptr,
           std::shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f)
    {
        counterOfAlivePerson++;
        std::cout << "ctor " << name << " counterOfAlivePerson=" << counterOfAlivePerson << std::endl;
    }
    ~Person()
    {
        counterOfAlivePerson--;
        std::cout << "delete " << name << " counterOfAlivePerson=" << counterOfAlivePerson << std::endl;
    }
};

std::shared_ptr<Person> initFamily(const std::string& name)
{
    std::shared_ptr<Person> mom(new Person(name + "'s mom"));
    std::shared_ptr<Person> dad(new Person(name + "'s dad"));
    std::shared_ptr<Person> kid(new Person(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

int Person::counterOfAlivePerson = 0;

int main()
{
    std::shared_ptr<Person> p = initFamily("nico");
    std::cout << "nico's family exists" << std::endl;
    std::cout << "- nico is shared " << p.use_count() << " times" << std::endl;

    // Instead of calling p->mother->kids[0]->name (for shared poiter)
    // Should be called lock():
    //std::cout << "- name of 1st kid of nico's mom: "
    //    << p->mother->kids[0].lock()->name << std::endl;
    std::cout << "kids[0].lock()" << std::endl;
    std::shared_ptr<Person> p2 = p->mother->kids[0].lock();
    //std::shared_ptr<Person> p2 = p->mother->kids[0];
    std::cout << "- nico is shared " << p.use_count() << " times" << std::endl;
    p = initFamily("jim");
    std::cout << "initFamily(\"jim\")" << std::endl;
    std::cout << "- nico is shared " << p2.use_count() << " times" << std::endl;
    std::cout << "jim's family exists" << std::endl;
    std::cout << "- jim is shared " << p.use_count() << " times" << std::endl;
}