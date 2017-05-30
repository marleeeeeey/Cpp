#pragma once

#include "StdPlus\StdPlus.h"
#include "EnglishWord.hpp"
#include "Dictionary.hpp"
#include "IniParser.hpp"

class FileName
{
public:
    FileName() { }
    
    FileName(const std::string & fullName)
    {
        makeFromFullName(fullName);
    }
    
    std::string getFullName() const
    {
        if (isEmpty)
            return "";

        return path + name + "." + ext;
    }

    bool empty() { return isEmpty; }

    std::string path;
    std::string name;
    std::string ext;

    void operator=(const std::string & fullName)
    {
        makeFromFullName(fullName);
    }

private:
    void makeFromFullName(const std::string & fullName)
    {
        isEmpty = false;

        size_t dotIndex = fullName.find_last_of('.');

        name = fullName.substr(0, dotIndex);

        size_t slashIndex = name.find_last_of('\\');
        path = name.substr(0, slashIndex + 1);
        name = name.substr(slashIndex + 1);

        ext = fullName.substr(dotIndex + 1);
    }

    bool isEmpty = true;
};

std::ostream & operator<<(std::ostream & os, const FileName & d)
{
    os
        << "path=" << d.path << "; "
        << "name=" << d.name << "; "
        << "ext=" << d.ext << "; "
        ;

    return os;
}

class AppData
{
public:
    static AppData & instanse()
    {
        static AppData appData;
        return appData;
    }

    stdplus::CmdParser cmd;
    FileName originalFileName;
    FileName exportFileName;
    FileName dictFileName = "dict.csv";
    std::string settingsFileName = "settings.ini";
    IniParser settings;

private:

    AppData() 
    {
        settings.load(settingsFileName);
    };

    AppData(const AppData &) = delete;
    void operator=(const AppData &) = delete;
};

std::set<std::string> getAllUniqueWords(const std::string & fileName, size_t minSizeWord = 3)
{
    AEXCEPT_IF(fileName.empty());

    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    
    std::ifstream originalFile(fileName);
    std::string fileAsString = stdplus::readText(originalFile);

    std::for_each(fileAsString.begin(), fileAsString.end(),
        [](char & ch)
    {
        if (ch >= 0 && ch <= 255 && !isalpha(ch) && ch != '\'')
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
        [](std::string & word) { word = stdplus::trim(word, " \n\'\t’‘’‘"); });

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

std::set<std::string> getIntersection(
    std::set<std::string> &first, std::set<std::string> &second)
{
    std::vector<std::string> onlyInFirst(first.size());
    auto it = std::set_intersection(first.begin(), first.end(),
        second.begin(), second.end(), onlyInFirst.begin());
    onlyInFirst.resize(it - onlyInFirst.begin());

    std::set<std::string> setWords;
    for (auto & word : onlyInFirst)
    {
        setWords.insert(word);
    }

    return setWords;
}

void parseCmd(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    auto & cmd = app.cmd;
    cmd.parseData(argc, argv);

    if (cmd.indexedValues().size() > 1)
    {
        app.originalFileName = cmd.indexedValues().at(1);
        app.exportFileName = app.originalFileName;
        app.exportFileName.name += "_tr";
    }
    else
    {
        app.exportFileName = "temp.txt";
    }
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

int main(int argc, char ** argv)
{
    auto & app = AppData::instanse();
    parseCmd(argc, argv);

    Dictionary dict;
    dict.load(app.dictFileName.getFullName());
    AVAR(dict.size());

    std::set<std::string> allTextWords;

    bool isCompareMode = app.originalFileName.empty() && app.settings.exist("compare");

    if (isCompareMode)
    {
        for (auto & fileName : app.settings.getValues("compare"))
        {
            auto curUniqueWords = getAllUniqueWords(fileName);
            if (allTextWords.empty())
            {
                allTextWords = curUniqueWords;
                continue;
            }

            std::vector<std::string> curWordUnion(curUniqueWords.size());

            std::set_intersection(allTextWords.begin(), allTextWords.end(),
                curUniqueWords.begin(), curUniqueWords.end(), curWordUnion.begin());

            allTextWords.clear();

            for (auto & w : curWordUnion)
                allTextWords.insert(w);
        }
    }
    else
    {
        allTextWords = getAllUniqueWords(app.originalFileName.getFullName());
    }

    AVAR(allTextWords.size());

    for (auto & w : allTextWords)
        dict.addWord(w);
    
    auto levelWords = dict.getWordsByLevel(0, 0);
    AVAR(levelWords.size());

    std::set<std::string> allUnknowWords;
    for (auto & engWord : levelWords)
        allUnknowWords.insert(engWord.getWord());

    auto unknownInThisText = getIntersection(allTextWords, allUnknowWords);
    {
        std::ofstream os(app.exportFileName.getFullName());
        for (auto & word : unknownInThisText)
            os << word << "\n";
    }

    std::string cmd = "call \"c:\\Program Files\\Notepad++\\notepad++.exe\" ";
    cmd += "\"" + app.exportFileName.getFullName() + "\"";
    AVAR(cmd);
    system(cmd.c_str());
    APAUSE;

    auto newUnknowWords = getAllUniqueWords(app.exportFileName.getFullName());
    AVAR(newUnknowWords.size());
    auto newKnowsWords = getOnlyInFirst(unknownInThisText, newUnknowWords);
    AVAR(newKnowsWords.size());

    int learningWordValue = 1;
    if (!newUnknowWords.empty() && isCompareMode)
    {
        ARED(learningWordValue);
    }

    for (auto & w : newUnknowWords)
        dict.addWord(w, learningWordValue);

    for (auto & w : newKnowsWords)
        dict.addWord(w, 1);

    if (!isCompareMode)
    {
        std::string originalString = stdplus::readText(app.originalFileName.getFullName());
        originalString = stdplus::tolower(originalString);

        for (auto & word : newUnknowWords)
        {
            std::string bigWord = word;
            for_each(bigWord.begin(), bigWord.end(),
                [](char & ch) { ch = toupper(ch); });

            try
            {
                replaceAll(originalString, word,
                    bigWord + "(" + dict.getTranslate(word) + ")");            	
            }
            catch (std::logic_error & exceptGetTraslate)
            {
                AVAR(exceptGetTraslate.what());
                AVAR(word);
            }
        }

        std::ofstream os(app.exportFileName.getFullName());
        os << originalString;
    }


    AVAR(dict.size());

    dict.saveAs(app.dictFileName.getFullName());

    APAUSE;
    return 0;

}
