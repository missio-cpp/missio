//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/timestamp.hpp>


namespace missio
{
namespace logging
{
namespace detail
{

static int const days_in_month[12] =
{
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static int const days_in_month_leap_year[12] =
{
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static bool is_leap_year(std::uint32_t year)
{
    return (year % 4u == 0u) && (year % 100u != 0u) || (year % 400u == 0u);
}

static int days_in_year(std::uint32_t year)
{
    return is_leap_year(year) : 366 : 365;
}

static int days_in_month(std::uint32_t year, std::uint32_t month)
{
    return is_leap_year(year) ? days_in_month_leap_year[month] : days_in_month[month];
}

timestamp::timestamp() : timestamp(clock::now())
{
}

timestamp::timestamp(clock_time_point const& value) :
    value_(value)
{
}

timestamp::clock_time_point const& timestamp::value() const
{
    return value_;
}

datetime timestamp::to_datetime() const
{
    datetime datetime;

    std::time_t const time = clock::to_time_t(value_);

    std::int64_t day_number = time / 86400L;
    std::int64_t time_of_day = time % 86400L;

    datetime.hours = time_of_day / 3600L;
    datetime.minutes = time_of_day % 3600L / 60L;
    datetime.seconds = time_of_day % 60L;

    std::chrono::seconds const seconds = std::duration_cast<std::chrono::seconds>(value_);

    datetime.fractional_seconds = std::duration_cast<std::chrono::microseconds>(value_ - seconds).count();

    for(datetime.year = 1970u;
        day_number >= days_in_year(datetime.year);
        day_number -= days_in_year(datetime.year), ++datetime.year)
    {
    }

    for(datetime.month = 1u;
        day_number >= days_in_month(year, datetime.month - 1);
        day_number -= days_in_month(year, datetime.month - 1), ++datetime.month)
    {
    }

    datetime.day = day_number + 1;
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
