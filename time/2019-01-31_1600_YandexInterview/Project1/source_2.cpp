#include <vector>
#include <string>
#include <iostream>

struct President
{
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << name << " - " << "I am being constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << name << " - " << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

int main()
{
    std::vector<President> elections;
    std::cout << "elections.reserve(1)\n";
    elections.reserve(1);
    std::cout << "emplace_back 1:\n";
    elections.emplace_back("Nelson Mandela 1", "South Africa", 1994);
    std::cout << "emplace_back 2:\n";
    elections.emplace_back("Nelson Mandela 2", "South Africa", 1994);

    std::vector<President> reElections;
    std::cout << "\nreElections.reserve(1):\n";
    reElections.reserve(1);
    std::cout << "\npush_back 1:\n";
    reElections.push_back(President("Franklin Delano Roosevelt 1", "the USA", 1936));
    std::cout << "\npush_back 2:\n";
    reElections.push_back(President("Franklin Delano Roosevelt 2", "the USA", 1936));

    std::cout << "\nContents:\n";
    for(President const& president : elections) {
        std::cout << president.name << " was elected president of "
            << president.country << " in " << president.year << ".\n";
    }
    for(President const& president : reElections) {
        std::cout << president.name << " was re-elected president of "
            << president.country << " in " << president.year << ".\n";
    }

    std::cin.get();
}