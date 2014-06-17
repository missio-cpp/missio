//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/thread_id.hpp>

// BOOST headers
#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)

// Windows headers
#include <windows.h>

#elif defined(BOOST_HAS_PTHREADS)

// POSIX headers
#include <pthread.h>

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
#if defined(BOOST_WINDOWS)
    return static_cast<unsigned long>(::GetCurrentThreadId());
#elif defined(BOOST_HAS_PTHREADS)
    return static_cast<unsigned long>(::pthread_self());
#else
#error Operating System is not supported
#endif
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
