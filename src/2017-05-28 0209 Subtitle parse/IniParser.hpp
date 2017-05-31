#pragma once

#include "StdPlus/StdPlus.h"

class IniParser
{
    using KeyValues = std::map<std::string, std::vector<std::string>>;
    friend std::ostream & operator<<(std::ostream & os, const IniParser & d);

public:
    IniParser()
    {

    }

    inline void load(const std::string & settingsFileName = "settings.ini")
    {
        std::ifstream ifs(settingsFileName);

        std::string line;
        while (std::getline(ifs, line))
        {
            auto assignSplit = stdplus::split(line, '=');

            if (assignSplit.size() > 2)
                throw std::logic_error("error settings in line " + line);

            std::string key = assignSplit.front();

            if (assignSplit.size() == 1)
            {
                m_keyValues[key];
                continue;
            }

            std::string allValues = assignSplit.at(1);
            std::vector<std::string> values = stdplus::split(allValues, ';');    

            for (auto & val : values)
                val = stdplus::trim(val);
            
            auto & targetValues = m_keyValues[key];
            targetValues.insert(targetValues.end(), values.begin(), values.end());
        }
        
    }

    inline std::vector<std::string> getValues(const std::string & key) const
    {
        return m_keyValues.at(key);
    }

    inline bool exist(const std::string & key) 
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

    inline KeyValues & keyValues() { return m_keyValues; }

private:

    KeyValues m_keyValues;

};
