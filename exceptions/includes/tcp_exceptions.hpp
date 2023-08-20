#ifndef TCP_EXCEPTIONS_H
#define TCP_EXCEPTIONS_H

#include <string>
#include <stdexcept>

#include "exceptions.hpp"

namespace ks {

class CreateSocketExceptions : public TcpExceptions 
{
public:
    using TcpExceptions::TcpExceptions;
};

class SetSocketExceptions : public TcpExceptions 
{
public:
    using TcpExceptions::TcpExceptions;
};

class BindingExceptions : public TcpExceptions 
{
public:
    using TcpExceptions::TcpExceptions;
};

class ConeccetSocketExceptions : public TcpExceptions 
{
public:
    using TcpExceptions::TcpExceptions;
};


} // namespace ks

#endif