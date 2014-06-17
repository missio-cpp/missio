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
    value_(get_current_time())
{
}

boost::posix_time::ptime const& timestamp::value() const
{
    return value_;
}

boost::posix_time::time_duration timestamp::elapsed() const
{
    return get_current_time() - value_;
}

boost::posix_time::ptime timestamp::get_current_time()
{
    return boost::posix_time::microsec_clock::local_time();
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
