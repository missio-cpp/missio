//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/convert.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/config.hpp>


BOOST_AUTO_TEST_SUITE(unicode_convert_test_suite)

struct convert_fixture
{
    convert_fixture() :
        hello_world_eng_wstr(L"Hello, world!"),
#if defined(WCHAR_MAX) && (WCHAR_MAX == 0xFFFF)
        hello_world_rus_wstr(L"\u041F\u0440\u0438\u0432\u0435\u0442, \u043C\u0438\u0440!")
#else   // wchar_t type stores UTF-32 code point
        hello_world_rus_wstr(L"\U0000041F\U00000440\U00000438\U00000432\U00000435\U00000442, \U0000043C\U00000438\U00000440!")
#endif
    {
#if defined(BOOST_NO_CXX11_UNICODE_LITERALS)
        char const hello_world_eng_utf8_c[] { '\x48', '\x65', '\x6C', '\x6C', '\x6F', ',', ' ', '\x77', '\x6F', '\x72', '\x6C', '\x64', '!' };
        char16_t const hello_world_eng_utf16_c[] { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F, 0x002C, 0x0020, 0x0077, 0x006F, 0x0072, 0x006C, 0x0064, 0x0021 };
        char32_t const hello_world_eng_utf32_c[] { 0x00000048, 0x00000065, 0x0000006C, 0x0000006C, 0x0000006F, 0x0000002C, 0x00000020, 0x00000077, 0x0000006F, 0x00000072, 0x0000006C, 0x00000064, 0x00000021 };

        char const hello_world_rus_utf8_c[] { '\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8', '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', ',', ' ', '\xD0', '\xBC', '\xD0', '\xB8', '\xD1', '\x80', '!' };
        char16_t const hello_world_rus_utf16_c[] { 0x041F, 0x0440, 0x0438, 0x0432, 0x0435, 0x0442, 0x002C, 0x0020, 0x043C, 0x0438, 0x0440, 0x0021 };
        char32_t const hello_world_rus_utf32_c[] { 0x0000041F, 0x00000440, 0x00000438, 0x00000432, 0x00000435, 0x00000442, 0x0000002C, 0x00000020, 0x0000043C, 0x00000438, 0x00000440, 0x00000021 };

        hello_world_eng_utf8.assign(std::begin(hello_world_eng_utf8_c), std::end(hello_world_eng_utf8_c));
        hello_world_eng_utf16.assign(std::begin(hello_world_eng_utf16_c), std::end(hello_world_eng_utf16_c));
        hello_world_eng_utf32.assign(std::begin(hello_world_eng_utf32_c), std::end(hello_world_eng_utf32_c));

        hello_world_rus_utf8.assign(std::begin(hello_world_rus_utf8_c), std::end(hello_world_rus_utf8_c));
        hello_world_rus_utf16.assign(std::begin(hello_world_rus_utf16_c), std::end(hello_world_rus_utf16_c));
        hello_world_rus_utf32.assign(std::begin(hello_world_rus_utf32_c), std::end(hello_world_rus_utf32_c));
#else
        hello_world_eng_utf8.assign(u8"Hello, world!");
        hello_world_eng_utf16.assign(u"Hello, world!");
        hello_world_eng_utf32.assign(U"Hello, world!");

        hello_world_rus_utf8.assign(u8"Привет, мир!");
        hello_world_rus_utf16.assign(u"Привет, мир!");
        hello_world_rus_utf32.assign(U"Привет, мир!");
#endif
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
