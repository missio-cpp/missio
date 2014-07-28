//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Implementation headers
#include "src/unicode/src/common.hpp"

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(unicode_common_impl_test_suite)

BOOST_AUTO_TEST_CASE(is_code_point_valid_test)
{
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x00000000u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x00000410u), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000FFFDu), true);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0010FFFFu), true);

    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0020FFFFu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000FFFEu), false);
    BOOST_CHECK_EQUAL(missio::unicode::impl::is_code_point_valid(0x0000FFFFu), false);
}

BOOST_AUTO_TEST_SUITE_END()
