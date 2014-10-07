//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_chrono_time_point_hpp
#define _missio_format_adapters_std_chrono_time_point_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/date_time.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<std::chrono::system_clock::time_point>
{
    template <typename Sink>
    static void format(Sink& sink, std::chrono::system_clock::time_point const& value)
    {
        date_time const date_time = make_date_time(value);

        write(sink, dec(date_time.year, 4), '-', date_time.get_month_name(), '-', dec(date_time.day, 2), ' ');
        write(sink, dec(date_time.hours, 2), ':', dec(date_time.minutes, 2), ':', dec(date_time.seconds, 2));

        if(date_time.microseconds > 0u)
            write(sink, '.', dec(date_time.microseconds, 6));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_chrono_time_point_hpp
