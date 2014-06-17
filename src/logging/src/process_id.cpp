//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/process_id.hpp>

// BOOST headers
#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)

// Windows headers
#include <windows.h>

#elif defined(BOOST_HAS_UNISTD_H)

// UNIX headers
#include <unistd.h>

#else
#error Operating System is not supported
#endif


namespace missio
{
namespace logging
{
namespace detail
{

process_id::process_id() :
    value_(get_current_process_id())
{
}

unsigned long process_id::value() const
{
    return value_;
}

unsigned long process_id::get_current_process_id()
{
#if defined(BOOST_WINDOWS)
    return static_cast<unsigned long>(::GetCurrentProcessId());
#elif defined(BOOST_HAS_UNISTD_H)
    return static_cast<unsigned long>(::getpid());
#else
#error Operating System is not supported
#endif
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
