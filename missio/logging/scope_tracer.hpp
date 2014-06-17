//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_scope_tracer_hpp
#define _missio_logging_scope_tracer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/severity.hpp>
#include <missio/logging/location.hpp>
#include <missio/logging/detail/timestamp.hpp>


namespace missio
{
namespace logging
{

class scope_tracer
{
public:
    scope_tracer(severity severity, location const& location);
    ~scope_tracer();

    scope_tracer(scope_tracer const&) = delete;
    scope_tracer& operator=(scope_tracer const&) = delete;

private:
    severity severity_;
    location location_;
    detail::timestamp timestamp_;
};

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_scope_tracer_hpp
