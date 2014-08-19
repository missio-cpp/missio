//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/datetime.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <string>


BOOST_AUTO_TEST_SUITE(logging_datetime_test_suite)

BOOST_AUTO_TEST_CASE(get_month_name_test)
{
    missio::logging::detail::datetime datetime;

    datetime.month = 0u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string(""));

    datetime.month = 1u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Jan"));

    datetime.month = 2u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Feb"));

    datetime.month = 3u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Mar"));

    datetime.month = 4u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Apr"));

    datetime.month = 5u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("May"));

    datetime.month = 6u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Jun"));

    datetime.month = 7u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Jul"));

    datetime.month = 8u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Aug"));

    datetime.month = 9u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Sep"));

    datetime.month = 10u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Oct"));

    datetime.month = 11u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Nov"));

    datetime.month = 12u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string("Dec"));

    datetime.month = 13u;
    BOOST_CHECK_EQUAL(std::string(datetime.get_month_name()), std::string(""));
}

BOOST_AUTO_TEST_SUITE_END()
