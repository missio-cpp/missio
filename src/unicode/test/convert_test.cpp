//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/convert.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(unicode_convert_test_suite)

struct convert_fixture
{
    convert_fixture() : 
        hello_world_eng_utf8(u8"Hello, world!"),
        hello_world_eng_utf16(u"Hello, world!"),
        hello_world_eng_utf32(U"Hello, world!"),
        hello_world_rus_utf8(u8"Привет, мир!"),
        hello_world_rus_utf16(u"Привет, мир!"),
        hello_world_rus_utf32(U"Привет, мир!"),
        hello_world_eng_wstr(L"Hello, world!"),
        hello_world_rus_wstr(L"Привет, мир!")
    {
    }

    std::string hello_world_eng_utf8;
    std::u16string hello_world_eng_utf16;
    std::u32string hello_world_eng_utf32;

    std::string hello_world_rus_utf8;
    std::u16string hello_world_rus_utf16;
    std::u32string hello_world_rus_utf32;

    std::wstring hello_world_eng_wstr;
    std::wstring hello_world_rus_wstr;
};

BOOST_FIXTURE_TEST_CASE(utf16_to_utf8_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_eng_utf16) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_rus_utf16) == hello_world_rus_utf8);

    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_eng_utf16.c_str()) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_rus_utf16.c_str()) == hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf8_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_eng_utf32) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_rus_utf32) == hello_world_rus_utf8);

    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_eng_utf32.c_str()) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_rus_utf32.c_str()) == hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(wide_string_to_utf8_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_eng_wstr) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_rus_wstr) == hello_world_rus_utf8);

    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_eng_wstr.c_str()) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8_string(hello_world_rus_wstr.c_str()) == hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(utf8_to_utf16_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_eng_utf8) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_rus_utf8) == hello_world_rus_utf16);

    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_eng_utf8.c_str()) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_rus_utf8.c_str()) == hello_world_rus_utf16);
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf16_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_eng_utf32) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_rus_utf32) == hello_world_rus_utf16);

    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_eng_utf32.c_str()) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_rus_utf32.c_str()) == hello_world_rus_utf16);
}

BOOST_FIXTURE_TEST_CASE(wide_string_to_utf16_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_eng_wstr) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_rus_wstr) == hello_world_rus_utf16);

    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_eng_wstr.c_str()) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16_string(hello_world_rus_wstr.c_str()) == hello_world_rus_utf16);
}

BOOST_FIXTURE_TEST_CASE(utf8_to_utf32_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_eng_utf8) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_rus_utf8) == hello_world_rus_utf32);

    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_eng_utf8.c_str()) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_rus_utf8.c_str()) == hello_world_rus_utf32);
}

BOOST_FIXTURE_TEST_CASE(utf16_to_utf32_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_eng_utf16) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_rus_utf16) == hello_world_rus_utf32);

    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_eng_utf16.c_str()) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_rus_utf16.c_str()) == hello_world_rus_utf32);
}

BOOST_FIXTURE_TEST_CASE(wide_string_to_utf32_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_eng_wstr) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_rus_wstr) == hello_world_rus_utf32);

    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_eng_wstr.c_str()) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32_string(hello_world_rus_wstr.c_str()) == hello_world_rus_utf32);
}

BOOST_FIXTURE_TEST_CASE(utf8_to_wide_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_eng_utf8) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_rus_utf8) == hello_world_rus_wstr);

    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_eng_utf8.c_str()) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_rus_utf8.c_str()) == hello_world_rus_wstr);
}

BOOST_FIXTURE_TEST_CASE(utf16_to_wide_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_eng_utf16) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_rus_utf16) == hello_world_rus_wstr);

    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_eng_utf16.c_str()) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_rus_utf16.c_str()) == hello_world_rus_wstr);
}

BOOST_FIXTURE_TEST_CASE(utf32_to_wide_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_eng_utf32) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_rus_utf32) == hello_world_rus_wstr);

    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_eng_utf32.c_str()) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide_string(hello_world_rus_utf32.c_str()) == hello_world_rus_wstr);
}

BOOST_AUTO_TEST_SUITE_END()
