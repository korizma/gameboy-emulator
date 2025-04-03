#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

namespace Logger
{
    void log(std::string msg)
    {
        std::cerr << msg << '\n';
    }
}




#endif