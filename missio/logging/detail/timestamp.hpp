//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_timestamp_hpp
#define _missio_logging_detail_timestamp_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <chrono>


namespace missio
{
namespace logging
{
namespace detail
{

class timestamp
{
public:
    typedef std::chrono::system_clock clock;
    typedef clock::time_point clock_time_point;

public:
    timestamp();

    timestamp(timestamp const&) = default;
    timestamp& operator=(timestamp const&) = default;

    timestamp(timestamp&&) = default;
    timestamp& operator=(timestamp&&) = default;

    clock_time_point const& value() const;

private:
    clock_time_point value_;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_timestamp_hpp
