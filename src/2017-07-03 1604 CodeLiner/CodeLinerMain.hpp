#pragma once

#include "StdPlus/StdPlus.h"


template <typename T>
double getAverage(const std::vector<T> & d)
{
    if (d.empty())
        return 0;

    T sum = std::accumulate(d.begin(), d.end(), (T)0);
    double average = (double)sum / d.size();
    return average;
}

class FileLiner
{
public:
    FileLiner(const std::string & fileName)
    {
        m_fileName = fileName;

        std::ifstream file(m_fileName);

        std::string line;

        while (std::getline(file, line))
        {
            line = stdplus::trim(line);

            if (isCommentLine(line))
            {
                m_commentLineCounter++;
                continue;
            }

            if (line == "")
            {
                m_emptyLineCounter++;
                continue;
            }
            
            m_fillLinesSize.push_back(line.size());

            m_fillLineCounter++;
        }

    }

    inline std::string getFileName() const { return m_fileName; }
    inline int getEmptyLineCounter() const { return m_emptyLineCounter; }
    inline int getFillLineCounter() const { return m_fillLineCounter; }
    inline int getCommentLineCounter() const { return m_commentLineCounter; }
    inline double getAverageLineSize() const { return getAverage(m_fillLinesSize); }

private:

    bool isCommentLine(const std::string & line)
    {
        if (line.size() < 2)
            return false;

        if (line[0] == '/' && line[1] == '/')
            return true;
        else
            return false;
    }

    std::string      m_fileName;
    int              m_emptyLineCounter   = 0;
    int              m_fillLineCounter    = 0;
    int              m_commentLineCounter = 0;
    std::vector<int> m_fillLinesSize;

};

std::ostream & operator<<(std::ostream & os, const FileLiner & d)
{
    std::string shortFileName = stdplus::fileNameFromFullPath(d.getFileName());

    os
        << "empty: "    << std::setw(4)  << d.getEmptyLineCounter()     << "; "
        << "comment: "  << std::setw(4)  << d.getCommentLineCounter()   << "; "
        << "fill: "     << std::setw(4)  << d.getFillLineCounter()      << "; "
        << "average: "  << std::setw(4)  << (int)d.getAverageLineSize() << "; "
        << "fileName: " /*<< std::setw(15)*/ << shortFileName << "; "
        ;

    return os;
}

class CodeLinerApplication
{
public:
    CodeLinerApplication(int argc, char ** argv)
    {
        createReportFile();

        if (argc > 1)
            m_mainDir = argv[1];

        AVAR(m_mainDir);
        ASPLIT;

        openSettingsFile();
        readFileMasksFromSettings();
        seachFileNames();
        calculateResult();
    }

    ~CodeLinerApplication()
    {
        LOG_STD_UNREGISTER_STREAM(m_reportFile);
        AMSG("You can see Report " + REPORT_FILE_NAME);
        APAUSE_MSG("PRESS ANY KEY FOR CLOSE CONSOLE");
    }

private:

    void calculateResult()
    {
        std::vector<FileLiner> fileLiners;

        for (const std::string & fileName : m_fileNames)
        {
            fileLiners.emplace_back(fileName);
        }

        AVAR(fileLiners);
        ASPLIT;

        std::vector<double> averageLineSizes;
        for (const auto & fileLiner : fileLiners)
        {
            m_sumEmpty += fileLiner.getEmptyLineCounter();
            m_sumFill += fileLiner.getFillLineCounter();
            m_sumComment += fileLiner.getCommentLineCounter();
            averageLineSizes.push_back(fileLiner.getAverageLineSize());
        }

        m_averageLineSize = getAverage(averageLineSizes);

        AVAR(m_sumEmpty);
        AVAR(m_sumComment);
        AVAR(m_sumFill);
        AVAR(m_averageLineSize);
        ASPLIT;
    }

    void seachFileNames()
    {
        AVAR(m_fileMasks);
        ASPLIT;

        m_fileNames = stdplus::getSubFilesIncludeSubfolders(m_mainDir, m_fileMasks);

        AVAR(m_fileNames);
        ASPLIT;
    }

    void readFileMasksFromSettings()
    {
        std::string fileMasksLine = m_settings.getValue<std::string>("fileMasks");
        auto fileMasks = stdplus::split(fileMasksLine, ';');
        m_fileMasks.insert(m_fileMasks.begin(), fileMasks.begin(), fileMasks.end());
    }

    void openSettingsFile()
    {
        try
        {
            m_settings.open(SETTINGS_FILE_NAME);
        }
        catch (std::logic_error &)
        {
            ARED(DEFAULT_FILE_MASKS);
            m_settings.setValue("fileMasks", DEFAULT_FILE_MASKS);
            m_settings.save(SETTINGS_FILE_NAME);
        }
    }

    void createReportFile()
    {
        m_reportFile.open(REPORT_FILE_NAME, std::ofstream::out);
        LOG_STD_REGISTER_STREAM(m_reportFile);

        AMSG("developer: Tyulenev  Sergey <marleeeeeey@gmail.com>");
        AMSG("all code: https://github.com/marleeeeeey/CppTests/blob/master/src/2017-07-03%201604%20CodeLiner/CodeLinerMain.hpp");
        ASPLIT;
    }


    const std::string SETTINGS_FILE_NAME = "settings.ini";
    const std::string REPORT_FILE_NAME   = stdplus::dateTimeStr() + " Report.txt";
    std::string       DEFAULT_FILE_MASKS = "*.cpp;*.h;*.hpp;*.cs;*.c;";

    stdplus::SimpleSettingsPlus m_settings;
    std::ofstream               m_reportFile;
    std::vector<std::string>    m_fileNames;
    std::vector<std::string>    m_fileMasks; 
    std::string                 m_mainDir = ".";

    int    m_sumEmpty        = 0;
    int    m_sumFill         = 0;
    int    m_sumComment      = 0;
    double m_averageLineSize = 0;

};

int main(int argc, char ** argv)
{
    CodeLinerApplication app(argc, argv);
}