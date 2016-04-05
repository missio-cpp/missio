//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Implementation headers
#include "src/unicode/src/utf16.hpp"

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <iterator>


BOOST_AUTO_TEST_SUITE(unicode_utf16_impl_test_suite)

BOOST_AUTO_TEST_CASE(is_surrogate_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xD800u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xDB7Fu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xDBFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xDC00u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xDDDDu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xDFFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0x0000u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0x0410u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_surrogate(0xE000u), false);
}

BOOST_AUTO_TEST_CASE(is_high_surrogate_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xD800u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xDB7Fu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xDBFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xDC00u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xDDDDu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xDFFFu), false);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0x0000u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0x0410u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_high_surrogate(0xE000u), false);
}

BOOST_AUTO_TEST_CASE(is_low_surrogate_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xDC00u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xDDDDu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xDFFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xD800u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xDB7Fu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xDBFFu), false);

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0x0000u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0x0410u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::is_low_surrogate(0xE000u), false);
}

BOOST_AUTO_TEST_CASE(make_code_point_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::make_code_point(0xD800u, 0xDC00u), 0x00010000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::make_code_point(0xDB7Fu, 0xDDDDu), 0x000EFDDDu);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::make_code_point(0xDB80u, 0xDE0Au), 0x000F020Au);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::make_code_point(0xDBFFu, 0xDFFFu), 0x0010FFFFu);
}

BOOST_AUTO_TEST_CASE(peek_next_code_point_test)
{
    std::uint16_t const test1[] { 0x007F };
    std::uint16_t const test2[] { 0x041F };
    std::uint16_t const test3[] { 0xFFFD };

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::peek_next(std::begin(test1), std::end(test1)), 0x0000007Fu);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::peek_next(std::begin(test2), std::end(test2)), 0x0000041Fu);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::peek_next(std::begin(test3), std::end(test3)), 0x0000FFFDu);
}

BOOST_AUTO_TEST_CASE(peek_next_surrogate_pair_code_point_test)
{
    std::uint16_t const test1[] { 0xD800, 0xDC00 };
    std::uint16_t const test2[] { 0xDB7F, 0xDDDD };
    std::uint16_t const test3[] { 0xDBFF, 0xDFFF };

    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::peek_next(std::begin(test1), std::end(test1)), 0x00010000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::peek_next(std::begin(test2), std::end(test2)), 0x000EFDDDu);
    BOOST_CHECK_EQUAL(missio::unicode::impl::utf16::peek_next(std::begin(test3), std::end(test3)), 0x0010FFFFu);
}

BOOST_AUTO_TEST_CASE(peek_next_on_empty_input_test)
{
    std::uint16_t const* test = nullptr;

    BOOST_CHECK_THROW(missio::unicode::impl::utf16::peek_next(test, test), missio::unicode::input_underflow_error);
}

BOOST_AUTO_TEST_CASE(peek_next_invalid_surrogate_pair_code_point_test)
{
    std::uint16_t const test1[] { 0xDB7F };           // lone high surrogate
    std::uint16_t const test2[] { 0xDC00 };           // lone low surrogate
    std::uint16_t const test3[] { 0xDB7F, 0x007F };   // high surrogate + non-surrogate
    std::uint16_t const test4[] { 0xDB7F, 0xDB7F };   // high surrogate + high surrogate

    BOOST_CHECK_THROW(missio::unicode::impl::utf16::peek_next(std::begin(test1), std::end(test1)), missio::unicode::invalid_utf16_code_unit);
    BOOST_CHECK_THROW(missio::unicode::impl::utf16::peek_next(std::begin(test2), std::end(test2)), missio::unicode::invalid_utf16_code_unit);
    BOOST_CHECK_THROW(missio::unicode::impl::utf16::peek_next(std::begin(test3), std::end(test3)), missio::unicode::invalid_utf16_code_unit);
    BOOST_CHECK_THROW(missio::unicode::impl::utf16::peek_next(std::begin(test4), std::end(test4)), missio::unicode::invalid_utf16_code_unit);
}

BOOST_AUTO_TEST_CASE(write_code_point_test)
{
    std::vector<std::uint16_t> vector;

    missio::unicode::impl::utf16::write(0x0000007Fu, std::back_inserter(vector));
    BOOST_CHECK_EQUAL(vector.size(), 1u);
    BOOST_CHECK_EQUAL(vector.front(), 0x007Fu);

    vector.clear();

    missio::unicode::impl::utf16::write(0x0000041Fu, std::back_inserter(vector));
    BOOST_CHECK_EQUAL(vector.size(), 1u);
    BOOST_CHECK_EQUAL(vector.front(), 0x041Fu);

    vector.clear();

    missio::unicode::impl::utf16::write(0x0000FFFDu, std::back_inserter(vector));
    BOOST_CHECK_EQUAL(vector.size(), 1u);
    BOOST_CHECK_EQUAL(vector.front(), 0xFFFDu);
}

BOOST_AUTO_TEST_CASE(write_surrogate_pair_code_point_test)
{
    std::vector<std::uint16_t> vector;

    missio::unicode::impl::utf16::write(0x00010000u, std::back_inserter(vector));
    BOOST_CHECK_EQUAL(vector.size(), 2u);
    BOOST_CHECK_EQUAL(vector.front(), 0xD800u);
    BOOST_CHECK_EQUAL(vector.back(), 0xDC00u);

    vector.clear();

    missio::unicode::impl::utf16::write(0x000EFDDDu, std::back_inserter(vector));
    BOOST_CHECK_EQUAL(vector.size(), 2u);
    BOOST_CHECK_EQUAL(vector.front(), 0xDB7Fu);
    BOOST_CHECK_EQUAL(vector.back(), 0xDDDDu);

    vector.clear();

    missio::unicode::impl::utf16::write(0x0010FFFFu, std::back_inserter(vector));
    BOOST_CHECK_EQUAL(vector.size(), 2u);
    BOOST_CHECK_EQUAL(vector.front(), 0xDBFFu);
    BOOST_CHECK_EQUAL(vector.back(), 0xDFFFu);
}

BOOST_AUTO_TEST_CASE(write_invalid_code_point_test)
{
    std::vector<std::uint16_t> vector;

    BOOST_CHECK_THROW(missio::unicode::impl::utf16::write(0x0000D800u, std::back_inserter(vector)), missio::unicode::invalid_utf32_code_point);
    BOOST_CHECK_THROW(missio::unicode::impl::utf16::write(0x0020FFFFu, std::back_inserter(vector)), missio::unicode::invalid_utf32_code_point);
    BOOST_CHECK_THROW(missio::unicode::impl::utf16::write(0x0000FFFEu, std::back_inserter(vector)), missio::unicode::invalid_utf32_code_point);
}

BOOST_AUTO_TEST_SUITE_END()
