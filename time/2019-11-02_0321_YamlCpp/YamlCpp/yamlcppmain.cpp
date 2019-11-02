#include <yaml-cpp/yaml.h>
#include <iostream>
#include <cassert>
#include <fstream>

void example01()
{
    YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
    for(std::size_t i = 0; i < primes.size(); i++) {
        std::cout << primes[i].as<int>() << "\n";
    }
    // or:
    for(YAML::const_iterator it = primes.begin(); it != primes.end(); ++it) {
        std::cout << it->as<int>() << "\n";
    }

    primes.push_back(13);

    for(std::size_t i = 0; i < primes.size(); i++) {
        std::cout << primes[i].as<int>() << "\n";
    }

    assert(primes.size() == 6);    
}

void example02_save()
{
    YAML::Emitter emitter;
    emitter << "Hello world!";
    emitter << "food next";
    emitter << YAML::BeginSeq;
    emitter << "eggs";
    emitter << "bread";
    emitter << "milk";
    emitter << YAML::EndSeq;
    emitter << "people next";
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "Ryan Braun";
    emitter << YAML::Key << "position";
    emitter << YAML::Value << "LF";
    emitter << YAML::EndMap;


    std::ofstream fout("file.yaml");
    fout << emitter.c_str();

 /*
Hello world!
---
food next
---
- eggs
- bread
- milk
---
people next
---
name: Ryan Braun
position: LF
*/
}

int main()
{
    example01();
    example02_save();
}
