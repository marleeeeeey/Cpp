#pragma once

#include "StdPlus\StdPlus.h"
#include "EnglishWord.hpp"
#include "Dictionary.hpp"

class ci_char_traits : public std::char_traits<char>
{
public:
    static bool eq(const _Elem & _Left, const _Elem & _Right)
    {
        return tolower(_Left) == tolower(_Right);
    }

    static bool lt(const _Elem & _Left, const _Elem & _Right)
    {
        return tolower(_Left) < tolower(_Right);
    }

    static int compare(const _Elem *s1, const _Elem *s2, size_t _Count)
    {
        return memicmp(s1, s2, _Count);
    }

    static const char * find(const _Elem * s, size_t n, const _Elem & a)
    {
        while (n-- && tolower(*s) != tolower(a))
        {
            ++s;
        }
        return n >= 0 ? s : 0;
    }

};

typedef std::basic_string<char, ci_char_traits> ci_string;

class AppData
{
public:
    static AppData & instanse()
    {
        static AppData appData;
        return appData;
    }

    stdplus::CmdParser cmd;
    std::string originalFileName;
    std::string exportFileName;
    std::string newSubFileName;
    const std::string dictFileName = "dict.txt";

private:

    AppData() {};
    AppData(const AppData &) = delete;
    void operator=(const AppData &) = delete;
};

std::set<std::string> getAllUniqueWords(const std::string & fileName, size_t minSizeWord = 3)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    
    std::ifstream originalFile(fileName);
    std::string fileAsString = stdplus::readText(originalFile);

    std::for_each(fileAsString.begin(), fileAsString.end(),
        [](char & ch)
    {
        if (!isalpha(ch) && ch != '\'')
        {
            ch = ' ';
        }
        else
        {
            ch = tolower(ch);
        }
    });

    std::vector<std::string> words = stdplus::split(fileAsString, ' ');

    for_each(words.begin(), words.end(),
        [](std::string & word) { word = stdplus::trim(word, " \n\'\t"); });

    auto it = std::remove_if(words.begin(), words.end(),
        [minSizeWord](const std::string & word)
    {
        if (word.size() < minSizeWord)
            return true;

        return false;
    });

    words.erase(it, words.end());

    std::sort(words.begin(), words.end());

    std::set<std::string> uniqueWords;

    for (auto & word : words)
    {
        uniqueWords.insert(word);
    }

    return uniqueWords;
}

void appendToDict(std::set<std::string> knowsWords)
{
    if (knowsWords.empty())
        return;

    auto & app = AppData::instanse();
    std::ofstream exportFile(app.dictFileName, std::ostream::app);

    exportFile << "-----------------------------------------------------\n";

    for (auto & word : knowsWords)
        exportFile << word << "\n";

}

std::set<std::string> getOnlyInFirst(
    std::set<std::string> &first, std::set<std::string> &second)
{
    std::vector<std::string> onlyInFirst(first.size());
    auto it = std::set_difference(first.begin(), first.end(),
        second.begin(), second.end(), onlyInFirst.begin());
    onlyInFirst.resize(it - onlyInFirst.begin());

    std::set<std::string> setWords;
    for (auto & word : onlyInFirst)
    {
        setWords.insert(word);
    }

    return setWords;
}

void changeWordsAndAppendToDict()
{
    auto & app = AppData::instanse();

    auto allWords = getAllUniqueWords(app.originalFileName);
    AVAR(allWords.size());

    // TODO !!! In dict include translate too
    auto dictWords = getAllUniqueWords(app.dictFileName);
    AVAR(dictWords.size());

    auto allWithoutDictWords = getOnlyInFirst(allWords, dictWords);
    AVAR(allWithoutDictWords.size());

    {
        std::ofstream exportFile(app.exportFileName);
        for (auto & word : allWithoutDictWords)
            exportFile << word << "\n";
    }

    AMSG("open " + stdplus::fileNamePrepare(app.exportFileName));
    APAUSE_MSG("Delete all knows words. After press any key.");

    auto newWords = getAllUniqueWords(app.exportFileName);
    AVAR(newWords.size());

    auto knowsWords = getOnlyInFirst(allWithoutDictWords, newWords);
    AVAR(knowsWords.size());

    appendToDict(knowsWords);
}

void parseCmd(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    cmd.parseData(argc, argv);
    app.originalFileName = cmd.indexedValues().at(1);
    app.exportFileName = app.originalFileName + "export";
    app.newSubFileName = app.originalFileName + "new";
}

struct DictLine
{
    std::string originalWord;
    std::string translate;

    std::string combo() const
    {
        std::string bigWord = originalWord;
        for_each(bigWord.begin(), bigWord.end(), 
            [](char & ch) { ch = toupper(ch); });

        return bigWord + "(" + translate + ")";
    }
};

std::ostream & operator<<(std::ostream & os, const DictLine & d)
{
    os
        << d.originalWord << "=" << d.translate
        ;

    return os;
}

std::vector<DictLine> readDict(const std::string & dictFileName)
{
    std::ifstream dictFile(dictFileName);

    std::string line;
    std::vector<DictLine> dictLines;

    int numLine = 0;

    while (std::getline(dictFile, line))
    {
        numLine++;

        auto splitLine = stdplus::split(line, '=');       

        if (splitLine.size() == 1)
        {
            splitLine.push_back("");
        }
        else if (splitLine.size() > 2)
        {
            AMSG("WARNING: more = in line " + stdplus::to_string(numLine) + ": " + line);
        }
        
        DictLine dictLine;
        dictLine.originalWord = stdplus::trim(splitLine.at(0));
        dictLine.translate = stdplus::trim(splitLine.at(1));

        dictLines.push_back(dictLine);
    }
    
    return dictLines;
}

void replaceAll(std::string & source, const std::string & oldValue, const std::string & newValue)
{
    size_t index = 0;

    while ((index = source.find(oldValue, index)) != std::string::npos)
    {
        size_t charAfterWordIndex = index + oldValue.size();
        if (charAfterWordIndex >= source.size())
            return;

        char charAfterWord = source.at(charAfterWordIndex);
        if (isalpha(charAfterWord))
        {
            index = charAfterWordIndex;
            continue;
        }


        size_t charBeforeWordIndex = index - 1;
        if (charBeforeWordIndex > 0)
        {
            char charBeforeWord = source.at(charBeforeWordIndex);
            if (isalpha(charBeforeWord))
            {
                index = charAfterWordIndex;
                continue;
            }
        }


        source.replace(index, oldValue.size(), newValue);
        index += newValue.size();
    };
}


int main1(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    parseCmd(argc, argv);

    changeWordsAndAppendToDict();
        
    AMSG("open file " + app.exportFileName);
    APAUSE_MSG("Add translate of all new words (Use =). After press any key...");
        
    auto dictLines = readDict(app.exportFileName);
    AVAR(dictLines.size());
    
    std::ifstream originalFile(app.originalFileName);
    std::string originalText = stdplus::readText(originalFile);
    originalFile.close();

    for_each(originalText.begin(), originalText.end(),
        [](char & ch) { ch = tolower(ch); });

    for (const auto & dictLine : dictLines)
    {        
        replaceAll(originalText, dictLine.originalWord, dictLine.combo());
    }

    std::ofstream newSubFile(app.newSubFileName);
    newSubFile << originalText;
    newSubFile.close();


    APAUSE_MSG("Press any key for quit application");

    return 0;
}


int main(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    parseCmd(argc, argv);

    Dictionary d;
    d.load(app.originalFileName);
    AVAR(d);
    
    APAUSE;
    return 0;

}
