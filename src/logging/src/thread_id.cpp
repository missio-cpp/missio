//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/thread_id.hpp>

#if defined(_WIN32) || defined(_WIN64)

// Windows headers
#include <windows.h>

#elif defined(__unix__) || defined(__unix)

// Unix headers
#include <unistd.h>

#if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)

// POSIX headers
#include <pthread.h>

#else
#error Operating System does not support POSIX threads
#endif

#else
#error Operating System is not supported
#endif


namespace missio
{
namespace logging
{
namespace detail
{

thread_id::thread_id() :
    value_(get_current_thread_id())
{
}

unsigned long thread_id::value() const
{
    return value_;
}

unsigned long thread_id::get_current_thread_id()
{
#if defined(_WIN32) || defined(_WIN64)
    return static_cast<unsigned long>(::GetCurrentThreadId());
#elif defined(__unix__) || defined(__unix)
#if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)
    return static_cast<unsigned long>(::pthread_self());
#else
#error Operating System does not support POSIX threads
#endif
#else
#error Operating System is not supported
#endif
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
