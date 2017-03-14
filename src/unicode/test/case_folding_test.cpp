//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/convert.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <iterator>


#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


BOOST_AUTO_TEST_SUITE(unicode_case_folding_test_suite)

namespace
{

template <typename T, std::size_t N>
constexpr std::size_t array_size(T const (&array)[N])
{
    return N;
}

}   // namespace

static char const* original_utf8[] { u8"Ὰͅ",  u8"Ⅷ", u8"eﬃcient",  u8"ﬂour",  u8"poſt", u8"poﬅ",  u8"ﬅop",  u8"tschüß",  u8"weiß",  u8"WEIẞ",  u8"ʀᴀʀᴇ", u8"στιγμας" };
static char const* casefold_utf8[] { u8"ὰι", u8"ⅷ", u8"efficient", u8"flour", u8"post", u8"post", u8"stop", u8"tschüss", u8"weiss", u8"weiss", u8"ʀᴀʀᴇ", u8"στιγμασ" };

BOOST_AUTO_TEST_CASE(utf8_fold_string_case_test)
{
    for(std::size_t i = 0; i < array_size(original_utf8); ++i)
    {
        BOOST_CHECK(missio::unicode::fold_case(std::string(original_utf8[i])) == std::string(casefold_utf8[i]));
    }
}

static char16_t const* original_utf16[] { u"Ὰͅ",  u"Ⅷ", u"eﬃcient",  u"ﬂour",  u"poſt", u"poﬅ",  u"ﬅop",  u"tschüß",  u"weiß",  u"WEIẞ",  u"ʀᴀʀᴇ", u"στιγμας" };
static char16_t const* casefold_utf16[] { u"ὰι", u"ⅷ", u"efficient", u"flour", u"post", u"post", u"stop", u"tschüss", u"weiss", u"weiss", u"ʀᴀʀᴇ", u"στιγμασ" };

BOOST_AUTO_TEST_CASE(utf16_fold_string_case_test)
{
    for(std::size_t i = 0; i < array_size(original_utf16); ++i)
    {
        BOOST_CHECK(missio::unicode::fold_case(std::u16string(original_utf16[i])) == std::u16string(casefold_utf16[i]));
    }
}

static char32_t const* original_utf32[] { U"Ὰͅ",  U"Ⅷ", U"eﬃcient",  U"ﬂour",  U"poſt", U"poﬅ",  U"ﬅop",  U"tschüß",  U"weiß",  U"WEIẞ",  U"ʀᴀʀᴇ", U"στιγμας" };
static char32_t const* casefold_utf32[] { U"ὰι", U"ⅷ", U"efficient", U"flour", U"post", U"post", U"stop", U"tschüss", U"weiss", U"weiss", U"ʀᴀʀᴇ", U"στιγμασ" };

BOOST_AUTO_TEST_CASE(utf32_fold_string_case_test)
{
    for(std::size_t i = 0; i < array_size(original_utf32); ++i)
    {
        BOOST_CHECK(missio::unicode::fold_case(std::u32string(original_utf32[i])) == std::u32string(casefold_utf32[i]));
    }
}

namespace
{

char const* turkish_locale_names[] { "tr_TR.UTF-8", "tr_TR.utf8", "turkish" };
char const* english_locale_names[] { "en_US.UTF-8", "en_US.utf8", "english" };

template <std::size_t N>
bool try_set_global_locale(char const* (&locale_names)[N])
{
    for(char const* locale_name : locale_names)
    {
        try
        {
            std::locale::global(std::locale(locale_name));
        }
        catch(std::runtime_error const&)
        {
            continue;
        }

        return true;
    }

    return false;
}

}   // namespace

BOOST_AUTO_TEST_CASE(utf8_fold_string_case_turkish_i_test)
{
    if(try_set_global_locale(turkish_locale_names))
    {
        BOOST_TEST_MESSAGE("Test UTF-8 case folding using locale: " << std::locale().name());

        BOOST_CHECK(missio::unicode::fold_case(std::string(u8"İ")) == std::string(u8"i"));
        BOOST_CHECK(missio::unicode::fold_case(std::string(u8"I")) == std::string(u8"ı"));
    }

    if(try_set_global_locale(english_locale_names))
    {
        BOOST_TEST_MESSAGE("Test UTF-8 case folding using locale: " << std::locale().name());

        BOOST_CHECK(missio::unicode::fold_case(std::string(u8"İ")) == std::string(u8"i̇"));
        BOOST_CHECK(missio::unicode::fold_case(std::string(u8"I")) == std::string(u8"i"));
    }
}

BOOST_AUTO_TEST_CASE(utf16_fold_string_case_turkish_i_test)
{
    if(try_set_global_locale(turkish_locale_names))
    {
        BOOST_TEST_MESSAGE("Test UTF-16 case folding using locale: " << std::locale().name());

        BOOST_CHECK(missio::unicode::fold_case(std::u16string(u"İ")) == std::u16string(u"i"));
        BOOST_CHECK(missio::unicode::fold_case(std::u16string(u"I")) == std::u16string(u"ı"));
    }

    if(try_set_global_locale(english_locale_names))
    {
        BOOST_TEST_MESSAGE("Test UTF-16 case folding using locale: " << std::locale().name());

        BOOST_CHECK(missio::unicode::fold_case(std::u16string(u"İ")) == std::u16string(u"i̇"));
        BOOST_CHECK(missio::unicode::fold_case(std::u16string(u"I")) == std::u16string(u"i"));
    }
}

BOOST_AUTO_TEST_CASE(utf32_fold_string_case_turkish_i_test)
{
    if(try_set_global_locale(turkish_locale_names))
    {
        BOOST_TEST_MESSAGE("Test UTF-32 case folding using locale: " << std::locale().name());

        BOOST_CHECK(missio::unicode::fold_case(std::u32string(U"İ")) == std::u32string(U"i"));
        BOOST_CHECK(missio::unicode::fold_case(std::u32string(U"I")) == std::u32string(U"ı"));
    }

    if(try_set_global_locale(english_locale_names))
    {
        BOOST_TEST_MESSAGE("Test UTF-32 case folding using locale: " << std::locale().name());

        BOOST_CHECK(missio::unicode::fold_case(std::u32string(U"İ")) == std::u32string(U"i̇"));
        BOOST_CHECK(missio::unicode::fold_case(std::u32string(U"I")) == std::u32string(U"i"));
    }
}

BOOST_AUTO_TEST_SUITE_END()
