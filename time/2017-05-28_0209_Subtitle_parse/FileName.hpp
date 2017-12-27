#pragma once

#include "StdPlus/StdInclude.h"

class FileName
{
public:
    inline FileName() { }

    inline FileName(const std::string & fullName)
    {
        makeFromFullName(fullName);
    }

    inline std::string getFullName() const
    {
        if (isEmpty)
            return "";

        return path + name + "." + ext;
    }

    inline std::string getShortName() const
    {
        if (isEmpty)
            return "";

        return name + "." + ext;
    }


    inline bool empty() { return isEmpty; }

    std::string path;
    std::string name;
    std::string ext;

    inline void operator=(const std::string & fullName)
    {
        makeFromFullName(fullName);
    }

private:
    inline void makeFromFullName(const std::string & fullName)
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

inline std::ostream & operator<<(std::ostream & os, const FileName & d)
{
    os
        << "path=" << d.path << "; "
        << "name=" << d.name << "; "
        << "ext=" << d.ext << "; "
        ;

    return os;
}
