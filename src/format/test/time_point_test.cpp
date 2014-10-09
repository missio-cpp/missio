//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/detail/time_point.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(format_time_point_test_suite)

BOOST_AUTO_TEST_CASE(unix_epoch_start_time_to_components_test)
{
    auto const value = std::chrono::system_clock::from_time_t(0LL);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, 1970u);
    BOOST_CHECK_EQUAL(time_point.month, 1u);
    BOOST_CHECK_EQUAL(time_point.day, 1u);

    BOOST_CHECK_EQUAL(time_point.hours, 0u);
    BOOST_CHECK_EQUAL(time_point.minutes, 0u);
    BOOST_CHECK_EQUAL(time_point.seconds, 0u);

    BOOST_CHECK_EQUAL(time_point.microseconds, 0u);
}

BOOST_AUTO_TEST_CASE(gigasecond_unix_time_to_components_test)
{
    auto const value = std::chrono::system_clock::from_time_t(1000000000LL);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, 2001u);
    BOOST_CHECK_EQUAL(time_point.month, 9u);
    BOOST_CHECK_EQUAL(time_point.day, 9u);

    BOOST_CHECK_EQUAL(time_point.hours, 1u);
    BOOST_CHECK_EQUAL(time_point.minutes, 46u);
    BOOST_CHECK_EQUAL(time_point.seconds, 40u);

    BOOST_CHECK_EQUAL(time_point.microseconds, 0u);
}

BOOST_AUTO_TEST_CASE(unix_time_with_microseconds_test)
{
    auto value = std::chrono::system_clock::from_time_t(1000000000LL) + std::chrono::microseconds(123456LL);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, 2001u);
    BOOST_CHECK_EQUAL(time_point.month, 9u);
    BOOST_CHECK_EQUAL(time_point.day, 9u);

    BOOST_CHECK_EQUAL(time_point.hours, 1u);
    BOOST_CHECK_EQUAL(time_point.minutes, 46u);
    BOOST_CHECK_EQUAL(time_point.seconds, 40u);

    BOOST_CHECK_EQUAL(time_point.microseconds, 123456u);
}

BOOST_AUTO_TEST_CASE(current_unix_time_to_components_test)
{
    std::time_t const time = std::time(nullptr);
    std::tm const tm = *std::gmtime(&time);

    auto const value = std::chrono::system_clock::from_time_t(time);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, static_cast<std::uint32_t>(tm.tm_year + 1900));
    BOOST_CHECK_EQUAL(time_point.month, static_cast<std::uint32_t>(tm.tm_mon + 1));
    BOOST_CHECK_EQUAL(time_point.day, static_cast<std::uint32_t>(tm.tm_mday));

    BOOST_CHECK_EQUAL(time_point.hours, static_cast<std::uint32_t>(tm.tm_hour));
    BOOST_CHECK_EQUAL(time_point.minutes, static_cast<std::uint32_t>(tm.tm_min));
    BOOST_CHECK_EQUAL(time_point.seconds, static_cast<std::uint32_t>(tm.tm_sec));

    BOOST_CHECK_EQUAL(time_point.microseconds, 0u);
}

BOOST_AUTO_TEST_CASE(get_month_name_test)
{
    missio::format::detail::time_point time_point;

    time_point.month = 0u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string(""));

    time_point.month = 1u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Jan"));

    time_point.month = 2u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Feb"));

    time_point.month = 3u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Mar"));

    time_point.month = 4u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Apr"));

    time_point.month = 5u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("May"));

    time_point.month = 6u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Jun"));

    time_point.month = 7u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Jul"));

    time_point.month = 8u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Aug"));

    time_point.month = 9u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Sep"));

    time_point.month = 10u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Oct"));

    time_point.month = 11u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Nov"));

    time_point.month = 12u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Dec"));

    time_point.month = 13u;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string(""));
}

BOOST_AUTO_TEST_SUITE_END()
