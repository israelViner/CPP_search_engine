#ifndef REQUEST_EXCEPTIONS_H
#define REQUEST_EXCEPTIONS_H

#include <string>
#include <stdexcept>

#include "exceptions.hpp"

namespace ks {

class ComunicationExceptions : public RequestExceptions 
{
public:
    using RequestExceptions::RequestExceptions;
};

class BrokenUrlExceptions : public RequestExceptions 
{
public:
    using RequestExceptions::RequestExceptions;
};


} // namespace ks

#endif