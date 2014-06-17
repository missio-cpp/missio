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

// BOOST headers
#include <boost/date_time.hpp>


namespace missio
{
namespace logging
{
namespace detail
{

class timestamp
{
public:
    timestamp();

    timestamp(timestamp const&) = default;
    timestamp& operator=(timestamp const&) = default;

    boost::posix_time::ptime const& value() const;
    boost::posix_time::time_duration elapsed() const;

private:
    static boost::posix_time::ptime get_current_time();

private:
    boost::posix_time::ptime value_;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_timestamp_hpp
