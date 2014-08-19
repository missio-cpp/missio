//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_datetime_hpp
#define _missio_logging_detail_datetime_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/inserters.hpp>
#include <missio/format/write.hpp>

// STL headers
#include <cstdint>


namespace missio
{
namespace logging
{
namespace detail
{

struct datetime
{
    std::uint32_t year;
    std::uint32_t month;
    std::uint32_t day;

    std::uint32_t hours;
    std::uint32_t minutes;
    std::uint32_t seconds;

    std::uint64_t fractional_seconds;

    char const* get_month_name() const;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<logging::detail::datetime>
{
    template <typename Sink>
    static void format(Sink& sink, logging::detail::datetime const& value)
    {
        write(sink, dec(value.year, 4), '-', value.get_month_name(), '-', dec(value.day, 2), ' ');
        write(sink, dec(value.hours, 2), ':', dec(value.minutes, 2), ':', dec(value.seconds, 2));

        if(value.fractional_seconds > 0u)
            write(sink, '.', dec(value.fractional_seconds, 6));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_logging_detail_datetime_hpp
