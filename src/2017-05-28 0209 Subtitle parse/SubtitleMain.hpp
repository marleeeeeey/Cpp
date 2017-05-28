#pragma once

#include "StdPlus\StdPlus.h"

class AppData
{
public:
    static AppData & instanse()
    {
        static AppData appData;
        return appData;
    }

    stdplus::CmdParser cmd;

private:

    AppData() {};
    AppData(const AppData &) = delete;
    void operator=(const AppData &) = delete;
};

void saveAllWords()
{
    auto & cmd = AppData::instanse().cmd;

    std::string subtitleFileName = cmd.indexedValues().at(1);
    std::string exportFileName = subtitleFileName + "export";
    AVAR(subtitleFileName);
    std::ifstream file(subtitleFileName);
    std::ofstream exportFile(exportFileName);
    std::string fileAsString = stdplus::readText(file);

    std::for_each(fileAsString.begin(), fileAsString.end(),
        [](char & ch)
    {
        if (!isalpha(ch))
        {
            ch = ' ';
        }
        else
        {
            ch = tolower(ch);
        }
    });

    std::vector<std::string> words = stdplus::split(fileAsString, ' ');

    auto it = std::remove_if(words.begin(), words.end(),
        [](const std::string & word)
    {
        if (word.size() < 3)
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


    for (auto & word : uniqueWords)
    {
        exportFile << word << "\n";
    }

}

void help()
{
    AFUN;
    APAUSE;
}

int main(int argc, char ** argv)
{
    auto & cmd = AppData::instanse().cmd;
    cmd.parseData(argc, argv);

    bool isSaveAllWords = cmd.getValue<bool>("saveAllWords", false);
    
    if (isSaveAllWords)
    {
        saveAllWords();
        return 0;
    }


    help();
}