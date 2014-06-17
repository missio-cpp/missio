//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/scope_tracer.hpp>
#include <missio/logging/common.hpp>

// STL headers
#include <cstdint>


namespace missio
{
namespace logging
{

scope_tracer::scope_tracer(severity severity, location const& location) :
    severity_(severity),
    location_(location)
{
    LOG_MESSAGE(severity_, location_, "enter");
}

scope_tracer::~scope_tracer()
{
    std::int64_t const total_milliseconds(timestamp_.elapsed().total_milliseconds());
    LOG_MESSAGE(severity_, location_, "exit, elapsed time: ", total_milliseconds, " ms");
}

}   // namespace logging
}   // namespace missio
