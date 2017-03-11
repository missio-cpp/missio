//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/exception.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <iterator>


BOOST_AUTO_TEST_SUITE(unicode_exception_test_suite)

BOOST_AUTO_TEST_CASE(input_underflow_error_exception_test)
{
    missio::unicode::input_underflow_error exception;

    BOOST_CHECK_EQUAL(exception.message(), R"(input underflow error)");
}

BOOST_AUTO_TEST_CASE(invalid_utf32_code_point_exception_test)
{
    missio::unicode::invalid_utf32_code_point exception1(0xFFFEu);

    BOOST_CHECK_EQUAL(exception1.code_point(), 0xFFFEu);
    BOOST_CHECK_EQUAL(exception1.message(), R"(invalid UTF-32 code point: U+FFFE)");

    missio::unicode::invalid_utf32_code_point exception2(0x11000Fu);

    BOOST_CHECK_EQUAL(exception2.code_point(), 0x11000Fu);
    BOOST_CHECK_EQUAL(exception2.message(), R"(invalid UTF-32 code point: U+11000F)");
}

BOOST_AUTO_TEST_CASE(invalid_utf16_code_unit_exception_test)
{
    missio::unicode::invalid_utf16_code_unit exception(0xD800u);

    BOOST_CHECK_EQUAL(exception.code_unit(), 0xD800u);
    BOOST_CHECK_EQUAL(exception.message(), R"(invalid or unexpected UTF-16 code unit: 0xD800)");
}

BOOST_AUTO_TEST_CASE(invalid_utf8_sequence_exception_test)
{
    char const sequence1[] { '\x80' };
    char const sequence2[] { '\xC0', '\x80' };
    char const sequence3[] { '\xE0', '\x80', '\x80' };
    char const sequence4[] { '\xF0', '\x80', '\x80', '\x80' };

    missio::unicode::invalid_utf8_sequence exception1(std::begin(sequence1), std::end(sequence1));

    BOOST_CHECK_EQUAL(exception1.sequence(), std::string(std::begin(sequence1), std::end(sequence1)));
    BOOST_CHECK_EQUAL(exception1.message(), R"(invalid UTF-8 sequence: 0x80)");

    missio::unicode::invalid_utf8_sequence exception2(std::begin(sequence2), std::end(sequence2));

    BOOST_CHECK_EQUAL(exception2.sequence(), std::string(std::begin(sequence2), std::end(sequence2)));
    BOOST_CHECK_EQUAL(exception2.message(), R"(invalid UTF-8 sequence: 0xC0 0x80)");

    missio::unicode::invalid_utf8_sequence exception3(std::begin(sequence3), std::end(sequence3));

    BOOST_CHECK_EQUAL(exception3.sequence(), std::string(std::begin(sequence3), std::end(sequence3)));
    BOOST_CHECK_EQUAL(exception3.message(), R"(invalid UTF-8 sequence: 0xE0 0x80 0x80)");

    missio::unicode::invalid_utf8_sequence exception4(std::begin(sequence4), std::end(sequence4));

    BOOST_CHECK_EQUAL(exception4.sequence(), std::string(std::begin(sequence4), std::end(sequence4)));
    BOOST_CHECK_EQUAL(exception4.message(), R"(invalid UTF-8 sequence: 0xF0 0x80 0x80 0x80)");
}

BOOST_AUTO_TEST_SUITE_END()
