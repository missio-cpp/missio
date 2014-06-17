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


BOOST_AUTO_TEST_SUITE(utf8_convert_test_suite)

struct convert_fixture
{
    convert_fixture() :
        hello_world_eng_utf8("Hello, world!"),
        hello_world_rus_utf8("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xD0\xBC\xD0\xB8\xD1\x80!"),                    // "Hello, world!" in Russian, in UTF-8
        hello_world_eng_wchar(L"Hello, world!"),
#if defined(WCHAR_MAX) && (WCHAR_MAX == 0xFFFF)
        hello_world_rus_wchar(L"\u041F\u0440\u0438\u0432\u0435\u0442, \u043C\u0438\u0440!")                                     // "Hello, world!" in Russian, in UTF-16
#else   // wchar_t type stores UTF-32 code point
        hello_world_rus_wchar(L"\U0000041F\U00000440\U00000438\U00000432\U00000435\U00000442, \U0000043C\U00000438\U00000440!") // "Hello, world!" in Russian, in UTF-32
#endif
    {
    }

    std::string hello_world_eng_utf8;
    std::string hello_world_rus_utf8;
    std::wstring hello_world_eng_wchar;
    std::wstring hello_world_rus_wchar;
};

BOOST_FIXTURE_TEST_CASE(utf8_to_utf16, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf8_to_utf32, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf16_to_utf8, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf16_to_utf32, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf8, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf32_to_utf16, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf8_to_wchar_convert_test, convert_fixture)
{
    std::wstring wchar_string;

    missio::unicode::utf8_to_wchar(
        hello_world_eng_utf8.begin(),
        hello_world_eng_utf8.end(),
        std::back_inserter(wchar_string));

    BOOST_CHECK(wchar_string == hello_world_eng_wchar);

    wchar_string.erase();

    missio::unicode::utf8_to_wchar(
        hello_world_rus_utf8.begin(),
        hello_world_rus_utf8.end(),
        std::back_inserter(wchar_string));

    BOOST_CHECK(wchar_string == hello_world_rus_wchar);
}

BOOST_FIXTURE_TEST_CASE(wchar_to_utf8_convert_test, convert_fixture)
{
    std::string utf8_string;

    missio::unicode::wchar_to_utf8(
        hello_world_eng_wchar.begin(),
        hello_world_eng_wchar.end(),
        std::back_inserter(utf8_string));

    BOOST_CHECK_EQUAL(utf8_string, hello_world_eng_utf8);

    utf8_string.erase();

    missio::unicode::wchar_to_utf8(
        hello_world_rus_wchar.begin(),
        hello_world_rus_wchar.end(),
        std::back_inserter(utf8_string));

    BOOST_CHECK_EQUAL(utf8_string, hello_world_rus_utf8);
}

BOOST_FIXTURE_TEST_CASE(utf8_utf16_utf8_round_trip_test, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(utf8_utf32_utf8_round_trip_test, convert_fixture)
{
    //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(string_convert_test, convert_fixture)
{
    BOOST_CHECK(hello_world_rus_wchar == missio::unicode::convert(hello_world_rus_utf8));
    BOOST_CHECK(hello_world_eng_wchar == missio::unicode::convert(hello_world_eng_utf8));

    BOOST_CHECK_EQUAL(hello_world_rus_utf8, missio::unicode::convert(hello_world_rus_wchar));
    BOOST_CHECK_EQUAL(hello_world_eng_utf8, missio::unicode::convert(hello_world_eng_wchar));
}

BOOST_AUTO_TEST_SUITE_END()
