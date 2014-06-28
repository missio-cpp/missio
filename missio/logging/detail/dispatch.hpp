//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_dispatch_hpp
#define _missio_logging_detail_dispatch_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/message.hpp>


#ifndef LOG_MAX_SEVERITY
#define LOG_MAX_SEVERITY      missio::logging::debug
#endif


namespace missio
{
namespace logging
{
namespace detail
{

void dispatch(message&& message);

template <typename ... Args>
void dispatch(severity severity, location const& location, Args const& ... args)
{
    if(severity <= LOG_MAX_SEVERITY)
        dispatch(message(severity, location, args...));
}

template <typename Format, typename ... Args>
void dispatch(Format const& format, severity severity, location const& location, Args const& ... args)
{
    if(severity <= LOG_MAX_SEVERITY)
        dispatch(message(format, severity, location, args...));
}

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_dispatch_hpp
