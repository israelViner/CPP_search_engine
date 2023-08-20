#ifndef CONFIG_EXCEPTIONS_H
#define CONFIG_EXCEPTIONS_H

#include <string>
#include <stdexcept>

#include "exceptions.hpp"

namespace ks {

class ConfigFileExceptions : public ConfigExceptions 
{
public:
    using ConfigExceptions::ConfigExceptions;
};

class TxtExceptions : public ConfigExceptions 
{
public:
    using ConfigExceptions::ConfigExceptions;
};

} // namespace ks

#endif