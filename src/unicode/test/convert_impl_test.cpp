//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Implementation headers
#include "src/unicode/src/convert.hpp"

// BOOST headers
#include <boost/test/unit_test.hpp>


#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


BOOST_AUTO_TEST_SUITE(unicode_convert_impl_test_suite)

struct convert_fixture
{
    convert_fixture() :
        hello_world_eng_utf8(u8"Hello, world!"),
        hello_world_eng_utf16(u"Hello, world!"),
        hello_world_eng_utf32(U"Hello, world!"),
        hello_world_rus_utf8(u8"Привет, мир!"),
        hello_world_rus_utf16(u"Привет, мир!"),
        hello_world_rus_utf32(U"Привет, мир!")
    {
    }

    std::string hello_world_eng_utf8;
    std::u16string hello_world_eng_utf16;
    std::u32string hello_world_eng_utf32;

    std::string hello_world_rus_utf8;
    std::u16string hello_world_rus_utf16;
    std::u32string hello_world_rus_utf32;
};

BOOST_FIXTURE_TEST_CASE(utf8_to_utf16_test, convert_fixture)
{
    std::u16string string;

    missio::unicode::impl::utf8_to_utf16(hello_world_eng_utf8.begin(), hello_world_eng_utf8.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_eng_utf16.begin(), hello_world_eng_utf16.end());

    string.erase();

    missio::unicode::impl::utf8_to_utf16(hello_world_rus_utf8.begin(), hello_world_rus_utf8.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_rus_utf16.begin(), hello_world_rus_utf16.end());
}

BOOST_FIXTURE_TEST_CASE(utf8_to_utf32_test, convert_fixture)
{
    std::u32string string;

    missio::unicode::impl::utf8_to_utf32(hello_world_eng_utf8.begin(), hello_world_eng_utf8.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_eng_utf32.begin(), hello_world_eng_utf32.end());

    string.erase();

    missio::unicode::impl::utf8_to_utf32(hello_world_rus_utf8.begin(), hello_world_rus_utf8.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_rus_utf32.begin(), hello_world_rus_utf32.end());
}

BOOST_FIXTURE_TEST_CASE(utf16_to_utf8_test, convert_fixture)
{
    std::string string;

    missio::unicode::impl::utf16_to_utf8(hello_world_eng_utf16.begin(), hello_world_eng_utf16.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_eng_utf8.begin(), hello_world_eng_utf8.end());

    string.erase();

    missio::unicode::impl::utf16_to_utf8(hello_world_rus_utf16.begin(), hello_world_rus_utf16.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_rus_utf8.begin(), hello_world_rus_utf8.end());
}

BOOST_FIXTURE_TEST_CASE(utf16_to_utf32_test, convert_fixture)
{
    std::u32string string;

    missio::unicode::impl::utf16_to_utf32(hello_world_eng_utf16.begin(), hello_world_eng_utf16.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_eng_utf32.begin(), hello_world_eng_utf32.end());

    string.erase();

    missio::unicode::impl::utf16_to_utf32(hello_world_rus_utf16.begin(), hello_world_rus_utf16.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_rus_utf32.begin(), hello_world_rus_utf32.end());
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf8_test, convert_fixture)
{
    std::string string;

    missio::unicode::impl::utf32_to_utf8(hello_world_eng_utf32.begin(), hello_world_eng_utf32.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_eng_utf8.begin(), hello_world_eng_utf8.end());

    string.erase();

    missio::unicode::impl::utf32_to_utf8(hello_world_rus_utf32.begin(), hello_world_rus_utf32.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_rus_utf8.begin(), hello_world_rus_utf8.end());
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf16_test, convert_fixture)
{
    std::u16string string;

    missio::unicode::impl::utf32_to_utf16(hello_world_eng_utf32.begin(), hello_world_eng_utf32.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_eng_utf16.begin(), hello_world_eng_utf16.end());

    string.erase();

    missio::unicode::impl::utf32_to_utf16(hello_world_rus_utf32.begin(), hello_world_rus_utf32.end(), std::back_inserter(string));
    BOOST_CHECK_EQUAL_COLLECTIONS(string.begin(), string.end(), hello_world_rus_utf16.begin(), hello_world_rus_utf16.end());
}

BOOST_AUTO_TEST_SUITE_END()
