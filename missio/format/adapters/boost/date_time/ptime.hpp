//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_date_time_ptime_hpp
#define _missio_format_adapters_boost_date_time_ptime_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/date_time.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::posix_time::ptime>
{
    template <typename Sink>
    static void format(Sink& sink, boost::posix_time::ptime const& value)
    {
        write(sink, value.date(), ' ', value.time_of_day());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_date_time_ptime_hpp
