//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_time_point_hpp
#define _missio_format_detail_time_point_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <cstdint>
#include <chrono>


namespace missio
{
namespace format
{
namespace detail
{

struct MISSIO_EXPORT time_point
{
    std::int32_t year;
    std::int32_t month;
    std::int32_t day;

    std::int32_t hours;
    std::int32_t minutes;
    std::int32_t seconds;
    std::int64_t microseconds;

    char const* month_name;
};

MISSIO_EXPORT time_point convert_time_point(std::chrono::system_clock::time_point const& value);

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_time_point_hpp
