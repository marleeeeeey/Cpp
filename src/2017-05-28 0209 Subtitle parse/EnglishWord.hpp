#pragma once

#include "StdPlus/StdPlus.h"

class EnglishWord
{
    friend bool operator<(const EnglishWord & _left, const EnglishWord & _right);
    friend std::ostream & operator<<(std::ostream & os, const EnglishWord & d);

public:
    explicit EnglishWord(const std::string & _word, const std::string & _translate = "")
    {
        word = _word;
        addTranslate(_translate);
        level = 0;
    }

    void addTranslate(const std::string & _translate)
    {
        if (_translate.empty())
            return;
        
        translates.insert(translatePrepare(_translate));
    }

    void levelUp() { ++level; }
    void levelDown() { --level; }

    void setLevel(int _level) { level = _level; }

    void merge(const EnglishWord & other)
    {
        if (this->word != other.word)
            throw std::exception("not equle words");

        level = (std::max)(level, other.level);

        translates.insert(other.translates.begin(), other.translates.end());
    }
    
private:
    std::string translatePrepare(const std::string & _translate)
    {
        // TODO
        return _translate;
    }

    std::string word;
    std::set<std::string> translates;
    int level;
};

bool operator<(const EnglishWord & _left, const EnglishWord & _right)
{
    return _left.word < _right.word;
}

std::ostream & operator<<(std::ostream & os, const EnglishWord & d)
{
    os
        << d.word << "; "
        << d.level << "; "
        ;

    for (auto & tranlate : d.translates)
    {
        os << tranlate << "; ";
    }

    return os;
}