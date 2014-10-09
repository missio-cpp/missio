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

// Application headers
#include <missio/format/detail/duration.hpp>


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
        bool output_started = false;

        duration const duration = convert_duration(value);

        write_duration(sink, duration.days, "d", output_started);
        write_duration(sink, duration.hours, "h", output_started);
        write_duration(sink, duration.minutes, "m", output_started);
        write_duration(sink, duration.seconds, "s", output_started);
        write_duration(sink, duration.milliseconds, "ms", output_started);
    }

    template <typename Sink, typename Value>
    static void write_duration(Sink& sink, Value const& value, char const* suffix, bool& output_started)
    {
        if(value > 0)
        {
            if(output_started)
            {
                write(sink, ' ');
            }

            write(sink, value, suffix);
            output_started = true;
        }
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_chrono_duration_hpp
