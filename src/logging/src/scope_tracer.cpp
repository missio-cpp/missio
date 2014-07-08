//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/scope_tracer.hpp>
#include <missio/logging/common.hpp>


namespace missio
{
namespace logging
{

scope_tracer::scope_tracer(severity severity, location const& location) :
    severity_(severity),
    location_(location),
    start_(clock::now())
{
    dispatch(severity_, location_, "enter");
}

scope_tracer::~scope_tracer()
{
    dispatch(severity_, location_, "exit, elapsed time: ", std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - start_).count(), " ms");
}

}   // namespace logging
}   // namespace missio
