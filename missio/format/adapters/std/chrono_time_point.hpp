//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_chrono_time_point_hpp
#define _missio_format_adapters_std_chrono_time_point_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/inserters_impl.hpp>
#include <missio/format/detail/time_point.hpp>


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
        time_point const time_point = convert_time_point(value);

        write(sink, dec(time_point.year, 4), '-', time_point.month_name, '-', dec(time_point.day, 2), ' ');
        write(sink, dec(time_point.hours, 2), ':', dec(time_point.minutes, 2), ':', dec(time_point.seconds, 2));

        if(time_point.microseconds > 0)
        {
            write(sink, '.', dec(time_point.microseconds, 6));
        }
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_chrono_time_point_hpp
