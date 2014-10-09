//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_date_time_time_duration_hpp
#define _missio_format_adapters_boost_date_time_time_duration_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/inserters.hpp>

// BOOST headers
#include <boost/date_time.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::posix_time::time_duration>
{
    template <typename Sink>
    static void format(Sink& sink, boost::posix_time::time_duration const& value)
    {
        write(sink, dec(value.hours(), 2), ':', dec(value.minutes(), 2), ':', dec(value.seconds(), 2));

        if(value.fractional_seconds() > 0)
            write(sink, '.', dec(value.fractional_seconds(), 6));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_date_time_time_duration_hpp
