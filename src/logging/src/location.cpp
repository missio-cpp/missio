//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/location.hpp>


namespace missio
{
namespace logging
{

location::location() :
    component_(nullptr),
    function_(nullptr),
    filename_(nullptr),
    line_(nullptr)
{
}

location::location(char const* component,
                   char const* function,
                   char const* filename,
                   char const* line) :
    component_(component),
    function_(function),
    filename_(filename),
    line_(line)
{
}

char const* location::component() const
{
    return component_;
}

char const* location::function() const
{
    return function_;
}

char const* location::filename() const
{
    return filename_;
}

char const* location::line() const
{
    return line_;
}

}   // namespace logging
}   // namespace missio
