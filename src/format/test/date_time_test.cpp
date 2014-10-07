//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/detail/date_time.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(format_date_time_test_suite)

BOOST_AUTO_TEST_CASE(unix_epoch_start_time_to_components_test)
{
    auto const time_point = std::chrono::system_clock::from_time_t(0LL);
    auto const date_time = missio::format::detail::make_date_time(time_point);

    BOOST_CHECK_EQUAL(date_time.year, 1970u);
    BOOST_CHECK_EQUAL(date_time.month, 1u);
    BOOST_CHECK_EQUAL(date_time.day, 1u);

    BOOST_CHECK_EQUAL(date_time.hours, 0u);
    BOOST_CHECK_EQUAL(date_time.minutes, 0u);
    BOOST_CHECK_EQUAL(date_time.seconds, 0u);

    BOOST_CHECK_EQUAL(date_time.microseconds, 0u);
}

BOOST_AUTO_TEST_CASE(gigasecond_unix_time_to_components_test)
{
    auto const time_point = std::chrono::system_clock::from_time_t(1000000000LL);
    auto const date_time = missio::format::detail::make_date_time(time_point);

    BOOST_CHECK_EQUAL(date_time.year, 2001u);
    BOOST_CHECK_EQUAL(date_time.month, 9u);
    BOOST_CHECK_EQUAL(date_time.day, 9u);

    BOOST_CHECK_EQUAL(date_time.hours, 1u);
    BOOST_CHECK_EQUAL(date_time.minutes, 46u);
    BOOST_CHECK_EQUAL(date_time.seconds, 40u);

    BOOST_CHECK_EQUAL(date_time.microseconds, 0u);
}

BOOST_AUTO_TEST_CASE(unix_time_with_microseconds_test)
{
    auto time_point = std::chrono::system_clock::from_time_t(1000000000LL) + std::chrono::microseconds(123456LL);
    auto const date_time = missio::format::detail::make_date_time(time_point);

    BOOST_CHECK_EQUAL(date_time.year, 2001u);
    BOOST_CHECK_EQUAL(date_time.month, 9u);
    BOOST_CHECK_EQUAL(date_time.day, 9u);

    BOOST_CHECK_EQUAL(date_time.hours, 1u);
    BOOST_CHECK_EQUAL(date_time.minutes, 46u);
    BOOST_CHECK_EQUAL(date_time.seconds, 40u);

    BOOST_CHECK_EQUAL(date_time.microseconds, 123456u);
}

BOOST_AUTO_TEST_CASE(current_unix_time_to_components_test)
{
    std::time_t const time = std::time(nullptr);
    std::tm const tm = *std::gmtime(&time);

    auto const time_point = std::chrono::system_clock::from_time_t(time);
    auto const date_time = missio::format::detail::make_date_time(time_point);

    BOOST_CHECK_EQUAL(date_time.year, static_cast<std::uint32_t>(tm.tm_year + 1900));
    BOOST_CHECK_EQUAL(date_time.month, static_cast<std::uint32_t>(tm.tm_mon + 1));
    BOOST_CHECK_EQUAL(date_time.day, static_cast<std::uint32_t>(tm.tm_mday));

    BOOST_CHECK_EQUAL(date_time.hours, static_cast<std::uint32_t>(tm.tm_hour));
    BOOST_CHECK_EQUAL(date_time.minutes, static_cast<std::uint32_t>(tm.tm_min));
    BOOST_CHECK_EQUAL(date_time.seconds, static_cast<std::uint32_t>(tm.tm_sec));

    BOOST_CHECK_EQUAL(date_time.microseconds, 0u);
}

BOOST_AUTO_TEST_CASE(get_month_name_test)
{
    missio::format::detail::date_time date_time;

    date_time.month = 0u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string(""));

    date_time.month = 1u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Jan"));

    date_time.month = 2u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Feb"));

    date_time.month = 3u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Mar"));

    date_time.month = 4u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Apr"));

    date_time.month = 5u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("May"));

    date_time.month = 6u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Jun"));

    date_time.month = 7u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Jul"));

    date_time.month = 8u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Aug"));

    date_time.month = 9u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Sep"));

    date_time.month = 10u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Oct"));

    date_time.month = 11u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Nov"));

    date_time.month = 12u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string("Dec"));

    date_time.month = 13u;
    BOOST_CHECK_EQUAL(std::string(date_time.get_month_name()), std::string(""));
}

BOOST_AUTO_TEST_SUITE_END()
