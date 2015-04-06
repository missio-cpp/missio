//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
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

    BOOST_CHECK_EQUAL(time_point.year, 1970);
    BOOST_CHECK_EQUAL(time_point.month, 1);
    BOOST_CHECK_EQUAL(time_point.day, 1);

    BOOST_CHECK_EQUAL(time_point.hours, 0);
    BOOST_CHECK_EQUAL(time_point.minutes, 0);
    BOOST_CHECK_EQUAL(time_point.seconds, 0);

    BOOST_CHECK_EQUAL(time_point.microseconds, 0);
}

BOOST_AUTO_TEST_CASE(gigasecond_unix_time_to_components_test)
{
    auto const value = std::chrono::system_clock::from_time_t(1000000000LL);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, 2001);
    BOOST_CHECK_EQUAL(time_point.month, 9);
    BOOST_CHECK_EQUAL(time_point.day, 9);

    BOOST_CHECK_EQUAL(time_point.hours, 1);
    BOOST_CHECK_EQUAL(time_point.minutes, 46);
    BOOST_CHECK_EQUAL(time_point.seconds, 40);

    BOOST_CHECK_EQUAL(time_point.microseconds, 0);
}

BOOST_AUTO_TEST_CASE(unix_time_with_microseconds_test)
{
    auto value = std::chrono::system_clock::from_time_t(1000000000LL) + std::chrono::microseconds(123456LL);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, 2001);
    BOOST_CHECK_EQUAL(time_point.month, 9);
    BOOST_CHECK_EQUAL(time_point.day, 9);

    BOOST_CHECK_EQUAL(time_point.hours, 1);
    BOOST_CHECK_EQUAL(time_point.minutes, 46);
    BOOST_CHECK_EQUAL(time_point.seconds, 40);

    BOOST_CHECK_EQUAL(time_point.microseconds, 123456);
}

BOOST_AUTO_TEST_CASE(current_unix_time_to_components_test)
{
    std::time_t const time = std::time(nullptr);
    std::tm const tm = *std::gmtime(&time);

    auto const value = std::chrono::system_clock::from_time_t(time);
    auto const time_point = missio::format::detail::convert_time_point(value);

    BOOST_CHECK_EQUAL(time_point.year, tm.tm_year + 1900);
    BOOST_CHECK_EQUAL(time_point.month, tm.tm_mon + 1);
    BOOST_CHECK_EQUAL(time_point.day, tm.tm_mday);

    BOOST_CHECK_EQUAL(time_point.hours, tm.tm_hour);
    BOOST_CHECK_EQUAL(time_point.minutes, tm.tm_min);
    BOOST_CHECK_EQUAL(time_point.seconds, tm.tm_sec);

    BOOST_CHECK_EQUAL(time_point.microseconds, 0);
}

BOOST_AUTO_TEST_CASE(get_month_name_test)
{
    missio::format::detail::time_point time_point;

    time_point.month = 0;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string(""));

    time_point.month = 1;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Jan"));

    time_point.month = 2;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Feb"));

    time_point.month = 3;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Mar"));

    time_point.month = 4;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Apr"));

    time_point.month = 5;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("May"));

    time_point.month = 6;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Jun"));

    time_point.month = 7;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Jul"));

    time_point.month = 8;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Aug"));

    time_point.month = 9;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Sep"));

    time_point.month = 10;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Oct"));

    time_point.month = 11;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Nov"));

    time_point.month = 12;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string("Dec"));

    time_point.month = 13;
    BOOST_CHECK_EQUAL(std::string(time_point.get_month_name()), std::string(""));
}

BOOST_AUTO_TEST_SUITE_END()
