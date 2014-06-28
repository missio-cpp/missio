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
#include <missio/logging/detail/dispatch.hpp>
#include <missio/logging/scope_tracer.hpp>


#define LOG_UNKNOWN                 <unknown>

#define LOG_STRINGIZE_LIT(x)        #x
#define LOG_STRINGIZE(x)            LOG_STRINGIZE_LIT(x)

#define LOG_SEV_FAILURE             missio::logging::failure
#define LOG_SEV_ERROR               missio::logging::error
#define LOG_SEV_WARNING             missio::logging::warning
#define LOG_SEV_NOTICE              missio::logging::notice
#define LOG_SEV_INFO                missio::logging::info
#define LOG_SEV_DEBUG               missio::logging::debug

#define LOG_LOCATION(component)     missio::logging::location(LOG_STRINGIZE(component), __FUNCTION__, __FILE__, LOG_STRINGIZE(__LINE__))

#define LOG_MESSAGE(severity, component, ...)     missio::logging::detail::dispatch(severity, LOG_LOCATION(component), __VA_ARGS__)

#define LOGF_MESSAGE(severity, component, format, ...)      missio::logging::detail::dispatch(format, severity, LOG_LOCATION(component), __VA_ARGS__)

#define LOG_FAILURE(...)    LOG_MESSAGE(LOG_SEV_FAILURE, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_ERROR(...)      LOG_MESSAGE(LOG_SEV_ERROR, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_WARNING(...)    LOG_MESSAGE(LOG_SEV_WARNING, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_NOTICE(...)     LOG_MESSAGE(LOG_SEV_NOTICE, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_INFO(...)       LOG_MESSAGE(LOG_SEV_INFO, LOG_UNKNOWN, __VA_ARGS__)
#define LOG_DEBUG(...)      LOG_MESSAGE(LOG_SEV_DEBUG, LOG_UNKNOWN, __VA_ARGS__)

#define LOGF_FAILURE(format, ...)     LOGF_MESSAGE(LOG_SEV_FAILURE, LOG_UNKNOWN, format, __VA_ARGS__)
#define LOGF_ERROR(format, ...)       LOGF_MESSAGE(LOG_SEV_ERROR, LOG_UNKNOWN, format, __VA_ARGS__)
#define LOGF_WARNING(format, ...)     LOGF_MESSAGE(LOG_SEV_WARNING, LOG_UNKNOWN, format, __VA_ARGS__)
#define LOGF_NOTICE(format, ...)      LOGF_MESSAGE(LOG_SEV_NOTICE, LOG_UNKNOWN, format, __VA_ARGS__)
#define LOGF_INFO(format, ...)        LOGF_MESSAGE(LOG_SEV_INFO, LOG_UNKNOWN, format, __VA_ARGS__)
#define LOGF_DEBUG(format, ...)       LOGF_MESSAGE(LOG_SEV_DEBUG, LOG_UNKNOWN, format, __VA_ARGS__)

#define LOG_COMP_FAILURE(component, ...)    LOG_MESSAGE(LOG_SEV_FAILURE, component, __VA_ARGS__)
#define LOG_COMP_ERROR(component, ...)      LOG_MESSAGE(LOG_SEV_ERROR, component, __VA_ARGS__)
#define LOG_COMP_WARNING(component, ...)    LOG_MESSAGE(LOG_SEV_WARNING, component, __VA_ARGS__)
#define LOG_COMP_NOTICE(component, ...)     LOG_MESSAGE(LOG_SEV_NOTICE, component, __VA_ARGS__)
#define LOG_COMP_INFO(component, ...)       LOG_MESSAGE(LOG_SEV_INFO, component, __VA_ARGS__)
#define LOG_COMP_DEBUG(component, ...)      LOG_MESSAGE(LOG_SEV_DEBUG, component, __VA_ARGS__)

#define LOGF_COMP_FAILURE(component, format, ...)     LOGF_MESSAGE(LOG_SEV_FAILURE, component, format, __VA_ARGS__)
#define LOGF_COMP_ERROR(component, format, ...)       LOGF_MESSAGE(LOG_SEV_ERROR, component, format, __VA_ARGS__)
#define LOGF_COMP_WARNING(component, format, ...)     LOGF_MESSAGE(LOG_SEV_WARNING, component, format, __VA_ARGS__)
#define LOGF_COMP_NOTICE(component, format, ...)      LOGF_MESSAGE(LOG_SEV_NOTICE, component, format, __VA_ARGS__)
#define LOGF_COMP_INFO(component, format, ...)        LOGF_MESSAGE(LOG_SEV_INFO, component, format, __VA_ARGS__)
#define LOGF_COMP_DEBUG(component, format, ...)       LOGF_MESSAGE(LOG_SEV_DEBUG, component, format, __VA_ARGS__)

#define LOG_TRACE_SCOPE()       missio::logging::scope_tracer scope_tracer(LOG_SEV_DEBUG, LOG_LOCATION(LOG_UNKNOWN))

#define LOG_COMP_TRACE_SCOPE(component)       missio::logging::scope_tracer scope_tracer(LOG_SEV_DEBUG, LOG_LOCATION(component))


namespace missio
{
namespace logging
{

void initialize();
void shutdown();

void start();
void stop();

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_common_hpp
