//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
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


BOOST_AUTO_TEST_SUITE(unicode_utf8_test_suite)

struct utf8_fixture
{
    utf8_fixture() :
        hello_world_eng("Hello, world!"),
        hello_world_rus("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xD0\xBC\xD0\xB8\xD1\x80!")   // "Hello, world!" in Russian, in UTF-8
    {
    }

    std::string hello_world_eng;
    std::string hello_world_rus;
};

BOOST_FIXTURE_TEST_CASE(length_text, utf8_fixture)
{
    BOOST_CHECK_EQUAL(missio::unicode::utf8::length(hello_world_eng), 13u);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::length(hello_world_rus), 12u);
}

BOOST_FIXTURE_TEST_CASE(replace_invalid_test, utf8_fixture)
{
    std::string valid1(hello_world_eng);
    std::string valid2(hello_world_rus);

    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("Hello, \xFF\xFE world!");
    std::string invalid3("Hello, \xE0\x80\x80\x80 world!");
    std::string invalid4("Hello, \x80\x80\x80\x80\x80 world!");
    std::string invalid5("\xC0\xE0\x80\xF0\x80\x80\xDF\xEF\xBF\xF7\xBF\xBF");

    missio::unicode::utf8::replace_invalid(valid1);
    BOOST_CHECK_EQUAL(valid1, hello_world_eng);

    missio::unicode::utf8::replace_invalid(valid2);
    BOOST_CHECK_EQUAL(valid2, hello_world_rus);

    missio::unicode::utf8::replace_invalid(invalid1, '?');
    BOOST_CHECK_EQUAL(invalid1, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid2, '?');
    BOOST_CHECK_EQUAL(invalid2, "Hello, ?? world!");

    missio::unicode::utf8::replace_invalid(invalid3, '?');
    BOOST_CHECK_EQUAL(invalid3, "Hello, ? world!");

    missio::unicode::utf8::replace_invalid(invalid4, '?');
    BOOST_CHECK_EQUAL(invalid4, "Hello, ????? world!");

    missio::unicode::utf8::replace_invalid(invalid5, '?');
    BOOST_CHECK_EQUAL(invalid5, std::string(6, '?'));
}

BOOST_FIXTURE_TEST_CASE(validate_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK_NO_THROW(missio::unicode::utf8::validate(hello_world_eng));
    BOOST_CHECK_NO_THROW(missio::unicode::utf8::validate(hello_world_rus));

    BOOST_CHECK_THROW(missio::unicode::utf8::validate(invalid1), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::utf8::validate(invalid2), missio::unicode::invalid_utf8_sequence);
}

BOOST_FIXTURE_TEST_CASE(is_valid_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(hello_world_eng), true);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(hello_world_rus), true);

    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(invalid1), false);
    BOOST_CHECK_EQUAL(missio::unicode::utf8::is_valid(invalid2), false);
}

BOOST_AUTO_TEST_SUITE_END()
