//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/exception.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <iterator>


BOOST_AUTO_TEST_SUITE(unicode_exception_test_suite)

BOOST_AUTO_TEST_CASE(invalid_utf32_code_point_exception_test)
{
    missio::unicode::invalid_utf32_code_point exception(0x0000FFFEu);

    BOOST_CHECK_EQUAL(exception.code_point(), 0x0000FFFEu);
    BOOST_CHECK_EQUAL(exception.message(), R"(invalid UTF-32 code point: \U0000FFFE)");
}

BOOST_AUTO_TEST_CASE(invalid_utf16_code_unit_exception_test)
{
    missio::unicode::invalid_utf16_code_unit exception(0xD800u);

    BOOST_CHECK_EQUAL(exception.code_unit(), 0xD800u);
    BOOST_CHECK_EQUAL(exception.message(), R"(invalid or unexpected UTF-16 code unit: \uD800)");
}

BOOST_AUTO_TEST_CASE(invalid_utf8_sequence_exception_test)
{
    char const sequence[] { '\xEF', '\xBB', '\xBF' };

    missio::unicode::invalid_utf8_sequence exception1(std::begin(sequence), std::end(sequence));

    BOOST_CHECK_EQUAL(exception1.sequence(), std::string(std::begin(sequence), std::end(sequence)));
    BOOST_CHECK_EQUAL(exception1.message(), R"(invalid UTF-8 sequence: \xEF\xBB\xBF)");
}

BOOST_AUTO_TEST_SUITE_END()
