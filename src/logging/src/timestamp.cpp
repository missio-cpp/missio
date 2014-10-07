//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/timestamp.hpp>


namespace missio
{
namespace logging
{
namespace detail
{

timestamp::timestamp() :
    value_(clock::now())
{
}

timestamp::clock_time_point const& timestamp::value() const
{
    return value_;
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
