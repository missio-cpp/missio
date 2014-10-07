//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_date_time_hpp
#define _missio_format_detail_date_time_hpp

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

struct date_time
{
    std::uint32_t year;
    std::uint32_t month;
    std::uint32_t day;

    std::uint32_t hours;
    std::uint32_t minutes;
    std::uint32_t seconds;
    std::uint64_t microseconds;

    char const* get_month_name() const;
};

date_time make_date_time(std::chrono::system_clock::time_point const& value);

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_date_time_hpp
