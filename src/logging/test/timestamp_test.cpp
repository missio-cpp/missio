//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/timestamp.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(logging_timestamp_test_suite)

BOOST_AUTO_TEST_CASE(unix_epoch_start_time_to_components_test)
{
    missio::logging::detail::timestamp const timestamp(std::chrono::system_clock::from_time_t(0LL));

    missio::logging::detail::datetime const datetime = timestamp.to_datetime();

    BOOST_CHECK_EQUAL(datetime.year, 1970u);
    BOOST_CHECK_EQUAL(datetime.month, 1u);
    BOOST_CHECK_EQUAL(datetime.day, 1u);

    BOOST_CHECK_EQUAL(datetime.hours, 0u);
    BOOST_CHECK_EQUAL(datetime.minutes, 0u);
    BOOST_CHECK_EQUAL(datetime.seconds, 0u);

    BOOST_CHECK_EQUAL(datetime.fractional_seconds, 0u);
}

BOOST_AUTO_TEST_CASE(gigasecond_unix_time_to_components_test)
{
    missio::logging::detail::timestamp const timestamp(std::chrono::system_clock::from_time_t(1000000000LL));

    missio::logging::detail::datetime const datetime = timestamp.to_datetime();

    BOOST_CHECK_EQUAL(datetime.year, 2001u);
    BOOST_CHECK_EQUAL(datetime.month, 9u);
    BOOST_CHECK_EQUAL(datetime.day, 9u);

    BOOST_CHECK_EQUAL(datetime.hours, 1u);
    BOOST_CHECK_EQUAL(datetime.minutes, 46u);
    BOOST_CHECK_EQUAL(datetime.seconds, 40u);

    BOOST_CHECK_EQUAL(datetime.fractional_seconds, 0u);
}

BOOST_AUTO_TEST_CASE(time_with_fractional_seconds_test)
{
    missio::logging::detail::timestamp const timestamp(std::chrono::system_clock::from_time_t(1000000000LL) + std::chrono::microseconds(123456LL));

    missio::logging::detail::datetime const datetime = timestamp.to_datetime();

    BOOST_CHECK_EQUAL(datetime.year, 2001u);
    BOOST_CHECK_EQUAL(datetime.month, 9u);
    BOOST_CHECK_EQUAL(datetime.day, 9u);

    BOOST_CHECK_EQUAL(datetime.hours, 1u);
    BOOST_CHECK_EQUAL(datetime.minutes, 46u);
    BOOST_CHECK_EQUAL(datetime.seconds, 40u);

    BOOST_CHECK_EQUAL(datetime.fractional_seconds, 123456u);
}

BOOST_AUTO_TEST_CASE(current_unix_time_to_components_test)
{
    std::time_t const time = std::time(nullptr);
    std::tm const tm = *std::gmtime(&time);

    missio::logging::detail::timestamp const timestamp(std::chrono::system_clock::from_time_t(time));

    missio::logging::detail::datetime const datetime = timestamp.to_datetime();

    BOOST_CHECK_EQUAL(datetime.year, static_cast<std::uint32_t>(tm.tm_year + 1900));
    BOOST_CHECK_EQUAL(datetime.month, static_cast<std::uint32_t>(tm.tm_mon + 1));
    BOOST_CHECK_EQUAL(datetime.day, static_cast<std::uint32_t>(tm.tm_mday));

    BOOST_CHECK_EQUAL(datetime.hours, static_cast<std::uint32_t>(tm.tm_hour));
    BOOST_CHECK_EQUAL(datetime.minutes, static_cast<std::uint32_t>(tm.tm_min));
    BOOST_CHECK_EQUAL(datetime.seconds, static_cast<std::uint32_t>(tm.tm_sec));

    BOOST_CHECK_EQUAL(datetime.fractional_seconds, 0u);
}

BOOST_AUTO_TEST_SUITE_END()
