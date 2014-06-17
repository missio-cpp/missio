//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_location_hpp
#define _missio_logging_location_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)


namespace missio
{
namespace logging
{

class location
{
public:
    location();

    location(char const* component,
             char const* function,
             char const* filename,
             char const* line);

    location(location const&) = default;
    location& operator=(location const&) = default;

    char const* component() const;
    char const* function() const;
    char const* filename() const;
    char const* line() const;

private:
    char const* component_;
    char const* function_;
    char const* filename_;
    char const* line_;
};

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_location_hpp
