//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/process_id.hpp>

#if defined(_WIN32) || defined(_WIN64)

// Windows headers
#include <windows.h>

#elif defined(__unix__) || defined(__unix)

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
#if defined(_WIN32) || defined(_WIN64)
    return static_cast<unsigned long>(::GetCurrentProcessId());
#elif defined(__unix__) || defined(__unix)
    return static_cast<unsigned long>(::getpid());
#else
#error Operating System is not supported
#endif
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
