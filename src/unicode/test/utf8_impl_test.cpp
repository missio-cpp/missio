//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Implementation headers
#include "src/unicode/src/utf8.hpp"

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <iterator>
#include <cstdint>
#include <string>


#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


BOOST_AUTO_TEST_SUITE(unicode_utf8_impl_test_suite)

struct utf8_fixture
{
    utf8_fixture() :
        hello_world_eng(u8"Hello, world!"),
        hello_world_rus(u8"Привет, мир!")   // "Hello, world!" in Russian, in UTF-8
    {
    }

    std::string empty_string;
    std::string hello_world_eng;
    std::string hello_world_rus;
};

BOOST_AUTO_TEST_CASE(is_continuation_octet_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_continuation_octet(0x80), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_continuation_octet(0x9F), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_continuation_octet(0xBF), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_continuation_octet(0x1A), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_continuation_octet(0xDF), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_continuation_octet(0xF4), false);
}

BOOST_AUTO_TEST_CASE(write_byte_order_mark_test)
{
    std::string string;

    missio::unicode::impl::utf8::write_byte_order_mark(std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, "\xEF\xBB\xBF");
}

BOOST_AUTO_TEST_CASE(skip_byte_order_mark_test)
{
    char const test1[] = "\xEF\xBB\xBF";          // UTF-8 BOM
    char const test2[] = "\xEF\xBB\xBF\xC4\x80";  // UTF-8 BOM + 2 octets code point
    char const test3[] = "\xFE\xBB\xFB";          // not a BOM
    char const test4[] = "\xEF\xBB";              // not a BOM

    char const* begin1 = std::begin(test1);
    char const* begin2 = std::begin(test2);
    char const* begin3 = std::begin(test3);
    char const* begin4 = std::begin(test4);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::skip_byte_order_mark(begin1, std::end(test1)), true);
    BOOST_CHECK_EQUAL(begin1, std::begin(test1) + 3);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::skip_byte_order_mark(begin2, std::end(test2)), true);
    BOOST_CHECK_EQUAL(begin2, std::begin(test2) + 3);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::skip_byte_order_mark(begin3, std::end(test3)), false);
    BOOST_CHECK_EQUAL(begin3, std::begin(test3));

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::skip_byte_order_mark(begin4, std::end(test4)), false);
    BOOST_CHECK_EQUAL(begin4, std::begin(test4));
}

BOOST_AUTO_TEST_CASE(starts_with_byte_order_mark_test)
{
    char const test1[] = "\xEF\xBB\xBF";          // UTF-8 BOM
    char const test2[] = "\xEF\xBB\xBF\xC4\x80";  // UTF-8 BOM + 2 octets code point
    char const test3[] = "\xFE\xBB\xFB";          // not a BOM
    char const test4[] = "\xEF\xBB";              // not a BOM

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::starts_with_byte_order_mark(std::begin(test1), std::end(test1)), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::starts_with_byte_order_mark(std::begin(test2), std::end(test2)), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::starts_with_byte_order_mark(std::begin(test3), std::end(test3)), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::starts_with_byte_order_mark(std::begin(test4), std::end(test4)), false);
}

BOOST_AUTO_TEST_CASE(peek_next_one_octet_code_point_test)
{
    char const test1[] = "\x00";
    char const test2[] = "\x7F";

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), 0x00000000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), 0x0000007Fu);
}

BOOST_AUTO_TEST_CASE(peek_next_two_octets_code_point_test)
{
    char const test1[] = "\xC2\x80";
    char const test2[] = "\xDF\xBF";

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), 0x00000080u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), 0x000007FFu);
}

BOOST_AUTO_TEST_CASE(peek_next_three_octets_code_point_test)
{
    char const test1[] = "\xE0\xA0\x80";
    char const test2[] = "\xE0\xBF\xBF";

    char const test3[] = "\xE1\x80\x80";
    char const test4[] = "\xEC\xBF\xBF";

    char const test5[] = "\xED\x80\x80";
    char const test6[] = "\xED\x9F\xBF";

    char const test7[] = "\xEE\x80\x80";
    char const test8[] = "\xEF\xBF\xBD";

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), 0x00000800u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), 0x00000FFFu);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), 0x00001000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test4), std::end(test4)), 0x0000CFFFu);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test5), std::end(test5)), 0x0000D000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test6), std::end(test6)), 0x0000D7FFu);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test7), std::end(test7)), 0x0000E000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test8), std::end(test8)), 0x0000FFFDu);
}

BOOST_AUTO_TEST_CASE(peek_next_four_octets_code_point_test)
{
    char const test1[] = "\xF0\x90\x80\x80";
    char const test2[] = "\xF0\x90\xBF\xBF";

    char const test3[] = "\xF1\x80\x80\x80";
    char const test4[] = "\xF3\xBF\xBF\xBF";

    char const test5[] = "\xF4\x80\x80\x80";
    char const test6[] = "\xF4\x8F\xBF\xBF";

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), 0x00010000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), 0x00010FFFu);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), 0x00040000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test4), std::end(test4)), 0x000FFFFFu);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test5), std::end(test5)), 0x00100000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_next(std::begin(test6), std::end(test6)), 0x0010FFFFu);
}

BOOST_AUTO_TEST_CASE(peek_next_on_empty_input_test)
{
    char const* test = nullptr;

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(test, test), missio::unicode::input_underflow_error);
}

BOOST_AUTO_TEST_CASE(peek_next_invalid_utf8_octets_test)
{
    char const test1[] = "\xFE";
    char const test2[] = "\xFF";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_unexpected_continuation_octets_test)
{
    char const test1[] = "\x80";
    char const test2[] = "\xBF";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_unexpected_first_continuation_octet_test)
{
    char const test1[] = "\xC4\x20";
    char const test2[] = "\xED\x9F\x20";
    char const test3[] = "\xF0\x9F\x80\x20";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_missing_last_continuation_octet_test)
{
    char const test1[] = "\xC4";
    char const test2[] = "\xED\x9F";
    char const test3[] = "\xF0\x9F\x80";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_overlong_ascii_utf8_sequence_test)
{
    char const test1[] = "\xC0\xAF";
    char const test2[] = "\xE0\x80\xAF";
    char const test3[] = "\xF0\x80\x80\xAF";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_overlong_max_utf8_sequence_test)
{
    char const test1[] = "\xC1\xBF";
    char const test2[] = "\xE0\x9F\xBF";
    char const test3[] = "\xF0\x8F\xBF\xBF";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_overlong_null_utf8_sequence_test)
{
    char const test1[] = "\xC0\x80";
    char const test2[] = "\xE0\x80\x80";
    char const test3[] = "\xF0\x80\x80\x80";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_unexpected_utf16_surrogate_test)
{
    char const test1[] = "\xED\xA0\x80";
    char const test2[] = "\xED\xAD\xBF";
    char const test3[] = "\xED\xAF\xBF";
    char const test4[] = "\xED\xBF\xBF";

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test4), std::end(test4)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(peek_next_invalid_utf32_code_points_test)
{
    char const test1[] = "\xEF\xBF\xBE";      // U+0000FFFE
    char const test2[] = "\xEF\xBF\xBF";      // U+0000FFFF
    char const test3[] = "\xF4\x9F\x80\x80";  // >U+0010FFFF

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(failed_next_should_not_modify_iterators_test)
{
    char const test[] = "\xF0\x9F\x80";   // missing last continuation octet
    auto iterator = std::begin(test);

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::next(iterator, std::end(test)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_EQUAL(iterator, std::begin(test));
}

BOOST_AUTO_TEST_CASE(peek_previous_code_point_test)
{
    char const test1[] = "\x1A";
    char const test2[] = "\xD0\x90";
    char const test3[] = "\xEE\x80\x80";
    char const test4[] = "\xF0\x9F\x80\x8A";

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test1)), std::begin(test1)), 0x0000001Au);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test2)), std::begin(test2)), 0x00000410u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test3)), std::begin(test3)), 0x0000E000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test4)), std::begin(test4)), 0x0001F00Au);
}

BOOST_AUTO_TEST_CASE(peek_previous_on_empty_input_test)
{
    char const* test = nullptr;

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_previous(test, test), missio::unicode::input_underflow_error);
}

BOOST_AUTO_TEST_CASE(peek_invalid_previous_code_point_test)
{
    char const test1[] = "\xFE";            // invalid UTF-8 octet
    char const test2[] = "\x80\xBF";        // dangling continuation octets
    char const test3[] = "\xE0\x80\x80";    // over-long UTF-8 sequence
    char const test4[] = "\xEF\xBF\xBE";    // invalid UTF-32 code point

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test1)), std::begin(test1)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test2)), std::begin(test2)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test3)), std::begin(test3)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::peek_previous(std::prev(std::end(test4)), std::begin(test4)), missio::unicode::invalid_utf8_sequence);
}

BOOST_AUTO_TEST_CASE(failed_previous_should_not_modify_iterators_test)
{
    char const test[] = "\x80\xBF";   // dangling continuation octets
    auto iterator = std::prev(std::end(test));

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::previous(iterator, std::begin(test)), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_EQUAL(iterator, std::prev(std::end(test)));
}

BOOST_AUTO_TEST_CASE(write_code_point_test)
{
    std::string string;

    missio::unicode::impl::utf8::write(0x0000007Bu, std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, "\x7B");

    string.erase();

    missio::unicode::impl::utf8::write(0x00000101u, std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, "\xC4\x81");

    string.erase();

    missio::unicode::impl::utf8::write(0x0000D7F4u, std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, "\xED\x9F\xB4");

    string.erase();

    missio::unicode::impl::utf8::write(0x0001F00Cu, std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, "\xF0\x9F\x80\x8C");
}

BOOST_AUTO_TEST_CASE(write_invalid_code_point_test)
{
    std::string string;

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::write(0x0000D800u, std::back_inserter(string)), missio::unicode::invalid_utf32_code_point);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::write(0x0020FFFFu, std::back_inserter(string)), missio::unicode::invalid_utf32_code_point);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::write(0x0000FFFEu, std::back_inserter(string)), missio::unicode::invalid_utf32_code_point);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::write(0x00110000u, std::back_inserter(string)), missio::unicode::invalid_utf32_code_point);
}

BOOST_FIXTURE_TEST_CASE(advance_text, utf8_fixture)
{
    std::string::iterator begin1 = std::begin(hello_world_eng);
    std::string::iterator begin2 = std::begin(hello_world_rus);

    BOOST_CHECK(missio::unicode::impl::utf8::advance(begin1, std::end(hello_world_eng), 3) == std::begin(hello_world_eng) + 3);
    BOOST_CHECK(missio::unicode::impl::utf8::advance(begin2, std::end(hello_world_rus), 3) == std::begin(hello_world_rus) + 6);
}

BOOST_FIXTURE_TEST_CASE(length_text, utf8_fixture)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::length(std::begin(empty_string), std::end(empty_string)), 0u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::length(std::begin(hello_world_eng), std::end(hello_world_eng)), 13u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::length(std::begin(hello_world_rus), std::end(hello_world_rus)), 12u);
}

BOOST_FIXTURE_TEST_CASE(replace_invalid_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");                   // unexpected continuation octet
    std::string invalid2("Hello, \xC1\x80 world!");               // invalid two octets code point
    std::string invalid3("Hello, \xE0\x80\x80 world!");           // invalid three octets code point
    std::string invalid4("Hello, \xF0\x80\x80\x80 world!");       // invalid four octets code point
    std::string invalid5("Hello, \xFF\xFE\xC0\xC1 world!");       // four invalid UTF-8 octets
    std::string invalid6("Hello, \xE0\x80\x80\x80 world!");       // over-long UTF-8 sequence
    std::string invalid7("Hello, \x80\x80\x80\x80\x80 world!");   // five unexpected continuation octets
    std::string invalid8("Hello, \xF1\x80\x80 world!");           // four octets code point with missing last continuation octet

    std::string string;

    missio::unicode::impl::utf8::replace_invalid(std::begin(empty_string), std::end(empty_string), std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, empty_string);

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(hello_world_eng), std::end(hello_world_eng), std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, hello_world_eng);

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(hello_world_rus), std::end(hello_world_rus), std::back_inserter(string));
    BOOST_CHECK_EQUAL(string, hello_world_rus);

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid1), std::end(invalid1), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid2), std::end(invalid2), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid3), std::end(invalid3), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid4), std::end(invalid4), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid5), std::end(invalid5), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ???? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid6), std::end(invalid6), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid7), std::end(invalid7), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ????? world!");

    string.erase();

    missio::unicode::impl::utf8::replace_invalid(std::begin(invalid8), std::end(invalid8), std::back_inserter(string), '?');
    BOOST_CHECK_EQUAL(string, "Hello, ? world!");
}

BOOST_FIXTURE_TEST_CASE(find_invalid_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("Hello, \xE0\x80\x80\x80 world!");
    std::string invalid3("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK(missio::unicode::impl::utf8::find_invalid(std::begin(empty_string), std::end(empty_string)) == std::end(empty_string));
    BOOST_CHECK(missio::unicode::impl::utf8::find_invalid(std::begin(hello_world_eng), std::end(hello_world_eng)) == std::end(hello_world_eng));
    BOOST_CHECK(missio::unicode::impl::utf8::find_invalid(std::begin(hello_world_rus), std::end(hello_world_rus)) == std::end(hello_world_rus));

    BOOST_CHECK(missio::unicode::impl::utf8::find_invalid(std::begin(invalid1), std::end(invalid1)) == std::begin(invalid1) + invalid1.find('\x80'));
    BOOST_CHECK(missio::unicode::impl::utf8::find_invalid(std::begin(invalid2), std::end(invalid2)) == std::begin(invalid2) + invalid2.find('\xE0'));
    BOOST_CHECK(missio::unicode::impl::utf8::find_invalid(std::begin(invalid3), std::end(invalid3)) == std::begin(invalid3) + invalid3.find('\xEF'));
}

BOOST_FIXTURE_TEST_CASE(validate_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK_NO_THROW(missio::unicode::impl::utf8::validate(empty_string.begin(), empty_string.end()));
    BOOST_CHECK_NO_THROW(missio::unicode::impl::utf8::validate(hello_world_eng.begin(), hello_world_eng.end()));
    BOOST_CHECK_NO_THROW(missio::unicode::impl::utf8::validate(hello_world_rus.begin(), hello_world_rus.end()));

    BOOST_CHECK_THROW(missio::unicode::impl::utf8::validate(invalid1.begin(), invalid1.end()), missio::unicode::invalid_utf8_sequence);
    BOOST_CHECK_THROW(missio::unicode::impl::utf8::validate(invalid2.begin(), invalid2.end()), missio::unicode::invalid_utf8_sequence);
}

BOOST_FIXTURE_TEST_CASE(is_valid_test, utf8_fixture)
{
    std::string invalid1("Hello, \x80 world!");
    std::string invalid2("\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82, \xEF\xBF\xBE \xD0\xBC\xD0\xB8\xD1\x80!");

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_valid(std::begin(empty_string), std::end(empty_string)), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_valid(std::begin(hello_world_eng), std::end(hello_world_eng)), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_valid(std::begin(hello_world_rus), std::end(hello_world_rus)), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_valid(std::begin(invalid1), std::end(invalid1)), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf8::is_valid(std::begin(invalid2), std::end(invalid2)), false);
}

BOOST_AUTO_TEST_SUITE_END()
