//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_chrono_duration_hpp
#define _missio_format_adapters_std_chrono_duration_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <chrono>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Rep, typename Period>
struct type_adapter<std::chrono::duration<Rep, Period>>
{
    template <typename Sink>
    static void format(Sink& sink, std::chrono::duration<Rep, Period> const& value)
    {
/*
//TODO: implement!

        duration const duration = make_duration(value);

        if(duration.hours > 0u)
            write(sink, duration.hours, "h");

        if(duration.minutes > 0u)
            write(sink, date_time.minutes, "m");

        if(duration.seconds > 0u)
            write(sink, date_time.seconds, "s");

        if(duration.microseconds > 0u)
            write(sink, date_time.microseconds, "ms");
*/
        write(sink, value.count());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_chrono_duration_hpp
