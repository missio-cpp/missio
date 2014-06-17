//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/unicode/impl/common.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(utf8_common_test_suite)

BOOST_AUTO_TEST_CASE(is_continuation_octet_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_continuation(0x80), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_continuation(0x9F), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_continuation(0xBF), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_continuation(0x1A), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_continuation(0xDF), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_continuation(0xF4), false);
}

BOOST_AUTO_TEST_CASE(is_surrogate_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xD800u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xDB7Fu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xDBFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xDC00u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xDDDDu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xDFFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0x0000u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0x0410u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_surrogate(0xE000u), false);
}

BOOST_AUTO_TEST_CASE(is_high_surrogate_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xD800u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xDB7Fu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xDBFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xDC00u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xDDDDu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xDFFFu), false);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0x0000u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0x0410u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_high_surrogate(0xE000u), false);
}

BOOST_AUTO_TEST_CASE(is_low_surrogate_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xDC00u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xDDDDu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xDFFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xD800u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xDB7Fu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xDBFFu), false);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0x0000u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0x0410u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_low_surrogate(0xE000u), false);
}

BOOST_AUTO_TEST_CASE(is_code_point_valid_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x00000000u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x00000410u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000FFFDu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0010FFFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000D800u), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000DFFAu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0020FFFFu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000FFFEu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000FFFFu), false);
}

BOOST_AUTO_TEST_CASE(make_code_point_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::make_code_point(0xD800u, 0xDC00u), 0x00010000u);
    BOOST_CHECK_EQUAL(missio::unicode::impl::make_code_point(0xDB7Fu, 0xDDDDu), 0x000EFDDDu);
    BOOST_CHECK_EQUAL(missio::unicode::impl::make_code_point(0xDB80u, 0xDE0Au), 0x000F020Au);
    BOOST_CHECK_EQUAL(missio::unicode::impl::make_code_point(0xDBFFu, 0xDFFFu), 0x0010FFFFu);
}

BOOST_AUTO_TEST_SUITE_END()
