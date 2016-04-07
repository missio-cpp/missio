//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/convert.hpp>
#include <missio/unicode/wchar.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


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
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_eng_utf16) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_rus_utf16) == hello_world_rus_utf8);

    BOOST_CHECK(missio::unicode::to_utf8(hello_world_eng_utf16.c_str()) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_rus_utf16.c_str()) == hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf8_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_eng_utf32) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_rus_utf32) == hello_world_rus_utf8);

    BOOST_CHECK(missio::unicode::to_utf8(hello_world_eng_utf32.c_str()) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_rus_utf32.c_str()) == hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(wide_string_to_utf8_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_eng_wstr) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_rus_wstr) == hello_world_rus_utf8);

    BOOST_CHECK(missio::unicode::to_utf8(hello_world_eng_wstr.c_str()) == hello_world_eng_utf8);
    BOOST_CHECK(missio::unicode::to_utf8(hello_world_rus_wstr.c_str()) == hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(utf8_to_utf16_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_eng_utf8) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_rus_utf8) == hello_world_rus_utf16);

    BOOST_CHECK(missio::unicode::to_utf16(hello_world_eng_utf8.c_str()) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_rus_utf8.c_str()) == hello_world_rus_utf16);
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf16_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_eng_utf32) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_rus_utf32) == hello_world_rus_utf16);

    BOOST_CHECK(missio::unicode::to_utf16(hello_world_eng_utf32.c_str()) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_rus_utf32.c_str()) == hello_world_rus_utf16);
}

BOOST_FIXTURE_TEST_CASE(wide_string_to_utf16_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_eng_wstr) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_rus_wstr) == hello_world_rus_utf16);

    BOOST_CHECK(missio::unicode::to_utf16(hello_world_eng_wstr.c_str()) == hello_world_eng_utf16);
    BOOST_CHECK(missio::unicode::to_utf16(hello_world_rus_wstr.c_str()) == hello_world_rus_utf16);
}

BOOST_FIXTURE_TEST_CASE(utf8_to_utf32_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_eng_utf8) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_rus_utf8) == hello_world_rus_utf32);

    BOOST_CHECK(missio::unicode::to_utf32(hello_world_eng_utf8.c_str()) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_rus_utf8.c_str()) == hello_world_rus_utf32);
}

BOOST_FIXTURE_TEST_CASE(utf16_to_utf32_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_eng_utf16) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_rus_utf16) == hello_world_rus_utf32);

    BOOST_CHECK(missio::unicode::to_utf32(hello_world_eng_utf16.c_str()) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_rus_utf16.c_str()) == hello_world_rus_utf32);
}

BOOST_FIXTURE_TEST_CASE(wide_string_to_utf32_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_eng_wstr) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_rus_wstr) == hello_world_rus_utf32);

    BOOST_CHECK(missio::unicode::to_utf32(hello_world_eng_wstr.c_str()) == hello_world_eng_utf32);
    BOOST_CHECK(missio::unicode::to_utf32(hello_world_rus_wstr.c_str()) == hello_world_rus_utf32);
}

BOOST_FIXTURE_TEST_CASE(utf8_to_wide_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_wide(hello_world_eng_utf8) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide(hello_world_rus_utf8) == hello_world_rus_wstr);

    BOOST_CHECK(missio::unicode::to_wide(hello_world_eng_utf8.c_str()) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide(hello_world_rus_utf8.c_str()) == hello_world_rus_wstr);
}

BOOST_FIXTURE_TEST_CASE(utf16_to_wide_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_wide(hello_world_eng_utf16) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide(hello_world_rus_utf16) == hello_world_rus_wstr);

    BOOST_CHECK(missio::unicode::to_wide(hello_world_eng_utf16.c_str()) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide(hello_world_rus_utf16.c_str()) == hello_world_rus_wstr);
}

BOOST_FIXTURE_TEST_CASE(utf32_to_wide_string_test, convert_fixture)
{
    BOOST_CHECK(missio::unicode::to_wide(hello_world_eng_utf32) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide(hello_world_rus_utf32) == hello_world_rus_wstr);

    BOOST_CHECK(missio::unicode::to_wide(hello_world_eng_utf32.c_str()) == hello_world_eng_wstr);
    BOOST_CHECK(missio::unicode::to_wide(hello_world_rus_utf32.c_str()) == hello_world_rus_wstr);
}

static char const* original_utf8[] { u8"eﬃcient",   u8"ﬂour",  u8"poſt", u8"poﬅ",  u8"ﬅop",  u8"tschüß",  u8"weiß",  u8"WEIẞ",  u8"ʀᴀʀᴇ" };
static char const* casefold_utf8[] { u8"efficient", u8"flour", u8"post", u8"post", u8"stop", u8"tschüss", u8"weiss", u8"weiss", u8"ʀᴀʀᴇ" };

BOOST_AUTO_TEST_CASE(utf8_fold_string_case_test)
{
    for(std::size_t i = 0; i < std::size(original_utf8); ++i)
    {
        BOOST_CHECK(missio::unicode::fold_case(std::string(original_utf8[i])) == std::string(casefold_utf8[i]));
    }
}

static char16_t const* original_utf16[] { u"eﬃcient",   u"ﬂour",  u"poſt", u"poﬅ",  u"ﬅop",  u"tschüß",  u"weiß",  u"WEIẞ",  u"ʀᴀʀᴇ" };
static char16_t const* casefold_utf16[] { u"efficient", u"flour", u"post", u"post", u"stop", u"tschüss", u"weiss", u"weiss", u"ʀᴀʀᴇ" };

BOOST_AUTO_TEST_CASE(utf16_fold_string_case_test)
{
    for(std::size_t i = 0; i < std::size(original_utf16); ++i)
    {
        BOOST_CHECK(missio::unicode::fold_case(std::u16string(original_utf16[i])) == std::u16string(casefold_utf16[i]));
    }
}

static char32_t const* original_utf32[] { U"eﬃcient",   U"ﬂour",  U"poſt", U"poﬅ",  U"ﬅop",  U"tschüß",  U"weiß",  U"WEIẞ",  U"ʀᴀʀᴇ" };
static char32_t const* casefold_utf32[] { U"efficient", U"flour", U"post", U"post", U"stop", U"tschüss", U"weiss", U"weiss", U"ʀᴀʀᴇ" };

BOOST_AUTO_TEST_CASE(utf32_fold_string_case_test)
{
    for(std::size_t i = 0; i < std::size(original_utf32); ++i)
    {
        BOOST_CHECK(missio::unicode::fold_case(std::u32string(original_utf32[i])) == std::u32string(casefold_utf32[i]));
    }
}

BOOST_AUTO_TEST_SUITE_END()
