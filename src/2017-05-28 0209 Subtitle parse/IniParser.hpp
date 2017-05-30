#pragma once

#include "StdPlus/StdPlus.h"

class IniParser
{
    friend std::ostream & operator<<(std::ostream & os, const IniParser & d);

public:
    IniParser()
    {

    }

    void load(const std::string & settingsFileName = "settings.ini")
    {
        std::ifstream ifs(settingsFileName);

        std::string line;
        while (std::getline(ifs, line))
        {
            auto assignSplit = stdplus::split(line, '=');

            if (assignSplit.size() > 2)
                throw std::logic_error("error settings in line " + line);

            std::string key = assignSplit.front();
            AVAR(key);

            if (assignSplit.size() == 1)
            {
                m_keyValues[key];
                continue;
            }

            std::string allValues = assignSplit.at(1);
            std::vector<std::string> values = stdplus::split(allValues, ';');    

            for (auto & val : values)
                val = stdplus::trim(val);

            AVAR(values);

            auto & targetValues = m_keyValues[key];
            targetValues.insert(targetValues.end(), values.begin(), values.end());
        }
        
    }

    std::vector<std::string> getValues(const std::string & key) const
    {
        return m_keyValues.at(key);
    }

    bool exist(const std::string & key) 
    {
        try
        {
            m_keyValues.at(key);
            return true;
        }
        catch (std::logic_error &)
        {
            return false;
        }
    }

private:
    std::map<std::string, std::vector<std::string>> m_keyValues;

};
