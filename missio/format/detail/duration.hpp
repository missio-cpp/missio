//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_duration_hpp
#define _missio_format_detail_duration_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <cstdint>
#include <chrono>


namespace missio
{
namespace format
{
namespace detail
{

struct duration
{
    std::int32_t days;
    std::int32_t hours;
    std::int32_t minutes;
    std::int32_t seconds;
    std::int32_t milliseconds;
};

template <typename Rep, typename Period>
duration convert_duration(std::chrono::duration<Rep, Period> const& value)
{
    using days_type = std::chrono::duration<std::int32_t, std::ratio<24 * 3600>>;

    auto const days = std::chrono::duration_cast<days_type>(value);
    auto const hours = std::chrono::duration_cast<std::chrono::hours>(value - days);
    auto const minutes = std::chrono::duration_cast<std::chrono::minutes>(value - days - hours);
    auto const seconds = std::chrono::duration_cast<std::chrono::seconds>(value - days - hours - minutes);
    auto const milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(value - days - hours - minutes - seconds);

    duration result;

    result.days = days.count();
    result.hours = hours.count();
    result.minutes = minutes.count();
    result.seconds = seconds.count();
    result.milliseconds = milliseconds.count();

    return result;
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_duration_hpp
