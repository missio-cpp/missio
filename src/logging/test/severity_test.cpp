//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/logging/severity.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(logging_severity_test_suite)

BOOST_AUTO_TEST_CASE(to_string_test)
{
    BOOST_CHECK_EQUAL(missio::logging::to_string(missio::logging::failure), "FAILURE");
    BOOST_CHECK_EQUAL(missio::logging::to_string(missio::logging::error),   "ERROR");
    BOOST_CHECK_EQUAL(missio::logging::to_string(missio::logging::warning), "WARNING");
    BOOST_CHECK_EQUAL(missio::logging::to_string(missio::logging::notice),  "NOTICE");
    BOOST_CHECK_EQUAL(missio::logging::to_string(missio::logging::info),    "INFO");
    BOOST_CHECK_EQUAL(missio::logging::to_string(missio::logging::debug),   "DEBUG");
}

BOOST_AUTO_TEST_CASE(from_string_test)
{
    BOOST_CHECK_EQUAL(missio::logging::from_string("FAILURE"), missio::logging::failure);
    BOOST_CHECK_EQUAL(missio::logging::from_string("ERROR"),   missio::logging::error);
    BOOST_CHECK_EQUAL(missio::logging::from_string("WARNING"), missio::logging::warning);
    BOOST_CHECK_EQUAL(missio::logging::from_string("NOTICE"),  missio::logging::notice);
    BOOST_CHECK_EQUAL(missio::logging::from_string("INFO"),    missio::logging::info);
    BOOST_CHECK_EQUAL(missio::logging::from_string("DEBUG"),   missio::logging::debug);

    // from_string should be case-insensitive
    BOOST_CHECK_EQUAL(missio::logging::from_string("debug"),   missio::logging::debug);

    // from_string should return DEBUG for invalid input strings
    BOOST_CHECK_EQUAL(missio::logging::from_string("invalid"), missio::logging::debug);
}

BOOST_AUTO_TEST_SUITE_END()
