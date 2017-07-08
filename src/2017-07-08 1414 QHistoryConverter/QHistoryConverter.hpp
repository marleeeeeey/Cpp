#pragma once

#include "StdPlus/StdPlus.h"

class HistoryApp
{
public:
    HistoryApp(int argc, char ** argv)
    {
        if (argc < 2)
            throw std::logic_error("ERROR: Use file name as first argument");

        m_fileName = argv[1];
        LOG_STD_VAR(m_fileName);

        fillParagraphsFromFile();
        makeResultFile();
    }

private:

    void fillParagraphsFromFile()
    {
        std::ifstream file(m_fileName);
        std::string line;

        std::string paragraph;

        while (std::getline(file, line))
        {
            int findResult = line.find(END_PART);

            if (findResult == std::string::npos)
            {
                if (!line.empty())
                {
                    paragraph.insert(paragraph.end(), line.begin(), line.end());
                    paragraph += " ";
                }
                continue;
            }

            m_paragraphs.push_back(paragraph);
            paragraph.clear();

            while (std::getline(file, line))
            {
                if (line == SPLITTER)
                    break;
            }
        }


    }

    void makeResultFile()
    {
        std::string resultFileName = stdplus::dateTimeStr()
            + " Result from " + stdplus::fileNameFromFullPath(m_fileName);

        std::ofstream resultFile(resultFileName);
        for (auto & line : m_paragraphs)
        {
            resultFile << line << std::endl;
        }

        LOG_STD_VAR(m_paragraphs.size());
    }
    
    const std::string SPLITTER = "================================";
    const std::string END_PART = "English to Russian]";
    std::vector<std::string> m_paragraphs;
    std::string              m_fileName;
};

int main(int argc, char ** argv)
{
    try
    {
        HistoryApp app(argc, argv);
    }
    catch (std::logic_error & eApp)
    {
        LOG_STD_VAR(eApp.what());
    }

    APAUSE;
}