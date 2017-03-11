//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/exception.hpp>
#include <missio/unicode/utf8.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <iterator>
#include <cstdint>
#include <string>


#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


BOOST_AUTO_TEST_SUITE(unicode_utf8_test_suite)

struct utf8_fixture
{
    utf8_fixture() :
        hello_world_eng("Hello, world!"),
        hello_world_rus("Привет, мир!")   // "Hello, world!" in Russian, in UTF-8
    {
    }

    std::string empty_string;
    std::string hello_world_eng;
    std::string hello_world_rus;
};

BOOST_FIXTURE_TEST_CASE(length_text, utf8_fixture)
{
    BOOST_CHECK_EQUAL(missio::unicode::utf8::length(empty_string), 0u);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::length(hello_world_eng), 13u);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::length(hello_world_rus), 12u);
}

BOOST_FIXTURE_TEST_CASE(replace_invalid_test, utf8_fixture)
{
    std::string valid1(empty_string);
    std::string valid2(hello_world_eng);
    std::string valid3(hello_world_rus);

    std::string invalid1("Hello, \x80 world!");                   // unexpected continuation octet
    std::string invalid2("Hello, \xC1\x80 world!");               // invalid two octets code point
    std::string invalid3("Hello, \xE0\x80\x80 world!");           // invalid three octets code point
    std::string invalid4("Hello, \xF0\x80\x80\x80 world!");       // invalid four octets code point
    std::string invalid5("Hello, \xFF\xFE\xC0\xC1 world!");       // four invalid UTF-8 octets
    std::string invalid6("Hello, \xE0\x80\x80\x80 world!");       // over-long UTF-8 sequence
    std::string invalid7("Hello, \x80\x80\x80\x80\x80 world!");   // five unexpected continuation octets
    std::string invalid8("Hello, \xF1\x80\x80 world!");           // four octets code point with missing last continuation octet

    missio::unicode::utf8::replace_invalid(valid1);
    BOOST_CHECK_EQUAL(valid1, empty_string);

    missio::unicode::utf8::replace_invalid(valid2);
    BOOST_CHECK_EQUAL(valid2, hello_world_eng);

    missio::unicode::utf8::replace_invalid(valid3);
    BOOST_CHECK_EQUAL(valid3, hello_world_rus);

    missio::unicode::utf8::replace_invalid(invalid1, '?');
    BOOST_CHECK_EQUAL(invalid1, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid2, '?');
    BOOST_CHECK_EQUAL(invalid2, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid3, '?');
    BOOST_CHECK_EQUAL(invalid3, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid4, '?');
    BOOST_CHECK_EQUAL(invalid4, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid5, '?');
    BOOST_CHECK_EQUAL(invalid5, "Hello, ???? world!");

    missio::unicode::utf8::replace_invalid(invalid6, '?');
    BOOST_CHECK_EQUAL(invalid6, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid7, '?');
    BOOST_CHECK_EQUAL(invalid7, "Hello, ????? world!");

    missio::unicode::utf8::replace_invalid(invalid8, '?');
    BOOST_CHECK_EQUAL(invalid8, "Hello, ? world!");
}

BOOST_FIXTURE_TEST_CASE(validate_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK_NO_THROW(missio::unicode::utf8::validate(empty_string));
    BOOST_CHECK_NO_THROW(missio::unicode::utf8::validate(hello_world_eng));
    BOOST_CHECK_NO_THROW(missio::unicode::utf8::validate(hello_world_rus));

    BOOST_CHECK_THROW(missio::unicode::utf8::validate(invalid1), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::utf8::validate(invalid2), missio::unicode::invalid_utf8_sequence);
}

BOOST_FIXTURE_TEST_CASE(is_valid_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(empty_string), true);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(hello_world_eng), true);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(hello_world_rus), true);

    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(invalid1), false);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(invalid2), false);
}

BOOST_AUTO_TEST_SUITE_END()
