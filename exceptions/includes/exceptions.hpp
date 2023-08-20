#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

namespace ks {

class RequestExceptions : public std::runtime_error 
{
public:
    using std::runtime_error::runtime_error;
};

class ConfigExceptions : public std::runtime_error 
{
public:
    using std::runtime_error::runtime_error;
};

class TcpExceptions : public std::runtime_error 
{
public:
    using std::runtime_error::runtime_error;
};

} // namespace ks

#endif