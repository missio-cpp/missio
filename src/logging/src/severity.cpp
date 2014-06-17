//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/severity.hpp>

// BOOST headers
#include <boost/algorithm/string.hpp>
#include <boost/range/size.hpp>


namespace missio
{
namespace logging
{

char const* strings[] =
{
    "FAILURE",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"
};

severity from_string(char const* str)
{
    for(std::size_t i = 0; i < boost::size(strings); ++i)
    {
        if(boost::algorithm::iequals(str, strings[i]))
            return static_cast<severity>(i);
    }

    return debug;
}

char const* to_string(severity severity)
{
    if(severity >= failure && severity <= debug)
        return strings[severity];

    return strings[debug];
}

}   // namespace logging
}   // namespace missio
