#pragma once

#include "StdPlus/StdPlus.h"
#include "EnglishWord.hpp"

// add 
// 1. time group
// 2. ...
// 3. getVector words
// 4. add property like as command line


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
            if (line.find(';') == std::string::npos)
                continue;

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

    void saveAs(const std::string & fileName, 
        std::set<std::string> fileUnknowns = {}, std::set<std::string> topWords = {})
    {
        std::ofstream os(fileName);
        
        std::vector<EnglishWord> vecWords;
        for (const auto & ew : m_words)
            vecWords.push_back(ew);

        auto itFile = std::partition(vecWords.begin(), vecWords.end(),
            [&](const EnglishWord & ew)
        {
            auto it = fileUnknowns.find(ew.getWord());
            return it != fileUnknowns.end();
        });

        auto itBest = std::partition(vecWords.begin(), itFile,
            [&](const EnglishWord & ew)
        {
            auto it = topWords.find(ew.getWord());
            return it != topWords.end();
        });


        std::for_each(vecWords.begin(), itBest,
            [&](const EnglishWord & ew) { os << ew << "\n"; });

        os << "------------------------------------------------------- \n";

        std::for_each(itBest, itFile,
            [&](const EnglishWord & ew) { os << ew << "\n"; });

        os << "------------------------------------------------------- \n";

        std::for_each(itFile, vecWords.end(),
            [&](const EnglishWord & ew) { os << ew << "\n"; });
    }

    void addWord(const EnglishWord & _word)
    {
        auto insertResult = m_words.insert(_word);

        if (insertResult.second == false)
        {             
            EnglishWord curWord = *insertResult.first;
            m_words.erase(insertResult.first);
            curWord.merge(_word);
            m_words.insert(curWord);
        }
    }

    void addWord(const std::string & _word, int _level = 0)
    {
        EnglishWord newWord(_word, "", _level);
        addWord(newWord);
    }

    void addWord(const std::string & _word, const std::string & _translate, int _level = 0)
    {
        EnglishWord newWord(_word, _translate, _level);
        addWord(newWord);
    }

    std::string getTranslate(const std::string & _word)
    {
        EnglishWord target(_word);
        auto it = m_words.find(target);
        if (it == m_words.end())
            throw std::logic_error("Not found this word!");

        return it->translate();
    }

    size_t size() { return m_words.size(); }

    std::vector<EnglishWord> getWordsByLevel(int minLevel = -999999, int maxLevel = 999999)
    {
        std::vector<EnglishWord> targerWords(m_words.size());
        auto it = std::copy_if(m_words.begin(), m_words.end(), targerWords.begin(),
            [minLevel, maxLevel](const EnglishWord & w) 
        {
            int level = w.level();

            if (level >= minLevel && level <= maxLevel)
                return true;

            return false;
        });

        targerWords.resize(std::distance(targerWords.begin(), it));

        return targerWords;
    }

private:
    std::set<EnglishWord> m_words;
};

std::ostream & operator<<(std::ostream & os, const Dictionary & d)
{
    os
        << "size=" << d.m_words.size() << "; "
        ;

    for (const auto & word : d.m_words)
    {
        os << word << "\n";
    }

    return os;
}