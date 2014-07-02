//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_severity_hpp
#define _missio_logging_severity_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <iostream>
#include <string>


namespace missio
{
namespace logging
{

enum severity
{
    failure,
    error,
    warning,
    notice,
    info,
    debug,
    trace
};

char const* to_string(severity severity);

inline std::ostream& operator<<(std::ostream& os, severity severity)
{
    os << to_string(severity);
    return os;
}

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_severity_hpp
