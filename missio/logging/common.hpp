//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_common_hpp
#define _missio_logging_common_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/scope_tracer.hpp>
#include <missio/logging/message.hpp>


#if !defined(LOG_MAX_SEVERITY)
#if defined(DEBUG) || defined(_DEBUG)
#define LOG_MAX_SEVERITY        missio::logging::debug
#else
#define LOG_MAX_SEVERITY        missio::logging::info
#endif
#endif

#define LOG_UNKNOWN             <unknown>

#define LOG_STRINGIZE_LIT(x)    #x
#define LOG_STRINGIZE(x)        LOG_STRINGIZE_LIT(x)

#define LOG_SEV_FAILURE         missio::logging::failure
#define LOG_SEV_ERROR           missio::logging::error
#define LOG_SEV_WARNING         missio::logging::warning
#define LOG_SEV_NOTICE          missio::logging::notice
#define LOG_SEV_INFO            missio::logging::info
#define LOG_SEV_DEBUG           missio::logging::debug
#define LOG_SEV_TRACE           missio::logging::trace

#define LOG_LOCATION(component)     missio::logging::location(LOG_STRINGIZE(component), __FUNCTION__, __FILE__, LOG_STRINGIZE(__LINE__))

#define LOG_MESSAGE(severity, component, ...)     missio::logging::dispatch(severity, LOG_LOCATION(component), __VA_ARGS__)

#define LOG_FAILURE(...)        LOG_MESSAGE(LOG_SEV_FAILURE, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_ERROR(...)          LOG_MESSAGE(LOG_SEV_ERROR, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_WARNING(...)        LOG_MESSAGE(LOG_SEV_WARNING, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_NOTICE(...)         LOG_MESSAGE(LOG_SEV_NOTICE, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_INFO(...)           LOG_MESSAGE(LOG_SEV_INFO, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_DEBUG(...)          LOG_MESSAGE(LOG_SEV_DEBUG, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_TRACE(...)          LOG_MESSAGE(LOG_SEV_TRACE, LOG_UNKNOWN, __VA_ARGS__)

#define LOG_TRACE_SCOPE()       missio::logging::scope_tracer scope_tracer(LOG_SEV_TRACE, LOG_LOCATION(LOG_UNKNOWN))

#define LOG_COMP_FAILURE(component, ...)        LOG_MESSAGE(LOG_SEV_FAILURE, component, __VA_ARGS__)
#define LOG_COMP_ERROR(component, ...)          LOG_MESSAGE(LOG_SEV_ERROR, component, __VA_ARGS__)
#define LOG_COMP_WARNING(component, ...)        LOG_MESSAGE(LOG_SEV_WARNING, component, __VA_ARGS__)
#define LOG_COMP_NOTICE(component, ...)         LOG_MESSAGE(LOG_SEV_NOTICE, component, __VA_ARGS__)
#define LOG_COMP_INFO(component, ...)           LOG_MESSAGE(LOG_SEV_INFO, component, __VA_ARGS__)
#define LOG_COMP_DEBUG(component, ...)          LOG_MESSAGE(LOG_SEV_DEBUG, component, __VA_ARGS__)
#define LOG_COMP_TRACE(component, ...)          LOG_MESSAGE(LOG_SEV_TRACE, component, __VA_ARGS__)

#define LOG_COMP_TRACE_SCOPE(component)         missio::logging::scope_tracer scope_tracer(LOG_SEV_TRACE, LOG_LOCATION(component))


namespace missio
{
namespace logging
{

void initialize();
void shutdown();

void start();
void stop();

void dispatch(message&& message);

template <typename ... Args>
void dispatch(severity severity, location const& location, Args const& ... args)
{
    if(severity <= LOG_MAX_SEVERITY)
        dispatch(message(severity, location, args...));
}

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_common_hpp
