#pragma once

#include "StdPlus/StdPlus.h"
#include "EnglishWord.hpp"


class Dictionary
{
    friend std::ostream & operator<<(std::ostream & os, const Dictionary & d);

public:
    explicit Dictionary()
    {

    }

    void load(const std::string & _fileName)
    {
        std::ifstream is(_fileName);
        std::string line;
        while (std::getline(is, line))
        {
            auto parts = stdplus::split(line, ';');
            for_each(parts.begin(), parts.end(), 
                [](std::string & p) { stdplus::trim(p, " \t\n\r\f\v,.!?"); });

            EnglishWord newWord(parts.at(0));

            if (parts.size() >= 2)
                newWord.setLevel(stdplus::to_int(parts.at(1)));

            if (parts.size() >= 3)
            {
                for_each(parts.begin() + 2, parts.end(),
                    [&newWord](const std::string & tr) {  newWord.addTranslate(tr); });
            }

            addWord(newWord);
        }
        
    }

    void saveAs(const std::string & _fileName)
    {
        std::ofstream os(_fileName);

        for (const auto & word : words)
        {
            os << word << "\n";
        }
    }

    void addWord(const EnglishWord & _word)
    {
        auto insertResult = words.insert(_word);

        if (insertResult.second == false)
        {             
            EnglishWord curWord = *insertResult.first;
            words.erase(insertResult.first);
            curWord.merge(_word);
            words.insert(curWord);
        }
    }

    void addWord(const std::string & _word, const std::string & _translate)
    {
        EnglishWord newWord(_word, _translate);
        addWord(newWord);
    }

private:
    std::set<EnglishWord> words;
};

std::ostream & operator<<(std::ostream & os, const Dictionary & d)
{
    os
        << "size=" << d.words.size() << "; "
        ;

    for (const auto & word : d.words)
    {
        os << word << "\n";
    }

    return os;
}