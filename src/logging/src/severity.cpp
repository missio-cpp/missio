//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/severity.hpp>


namespace missio
{
namespace logging
{

static char const* strings[] =
{
    "FAILURE",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG",
    "TRACE"
};

char const* to_string(severity severity)
{
    if(severity >= failure && severity <= trace)
        return strings[severity];

    return "<UNKNOWN>";
}

}   // namespace logging
}   // namespace missio
