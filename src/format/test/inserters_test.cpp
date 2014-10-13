//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/format.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(format_modifiers_test_suite)

BOOST_AUTO_TEST_CASE(right_align_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::right_align("string", 16));
    BOOST_CHECK_EQUAL(sink, "          string");

    sink.erase();

    missio::format::write(sink, missio::format::right_align("string", 16, '#'));
    BOOST_CHECK_EQUAL(sink, "##########string");

    sink.erase();

    missio::format::write(sink, missio::format::right_align("string", 5));
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::right_align("string", 16));
    BOOST_CHECK_EQUAL(sink, "          string");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::right_align("string", 16, '#'));
    BOOST_CHECK_EQUAL(sink, "##########string");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::right_align("string", 5));
    BOOST_CHECK_EQUAL(sink, "string");
}

BOOST_AUTO_TEST_CASE(left_align_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::left_align("string", 16));
    BOOST_CHECK_EQUAL(sink, "string          ");

    sink.erase();

    missio::format::write(sink, missio::format::left_align("string", 16, '#'));
    BOOST_CHECK_EQUAL(sink, "string##########");

    sink.erase();

    missio::format::write(sink, missio::format::left_align("string", 5));
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::left_align("string", 16));
    BOOST_CHECK_EQUAL(sink, "string          ");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::left_align("string", 16, '#'));
    BOOST_CHECK_EQUAL(sink, "string##########");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::left_align("string", 5));
    BOOST_CHECK_EQUAL(sink, "string");
}

BOOST_AUTO_TEST_CASE(repeat_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::repeat("ab", 10));
    BOOST_CHECK_EQUAL(sink, "abababababababababab");

    sink.erase();

    missio::format::write(sink, missio::format::repeat(123, 5));
    BOOST_CHECK_EQUAL(sink, "123123123123123");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::repeat("ab", 10));
    BOOST_CHECK_EQUAL(sink, "abababababababababab");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::repeat(123, 5));
    BOOST_CHECK_EQUAL(sink, "123123123123123");
}

BOOST_AUTO_TEST_CASE(upper_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::upper("abcde"));
    BOOST_CHECK_EQUAL(sink, "ABCDE");

    sink.erase();

    missio::format::write(sink, missio::format::upper(12345));
    BOOST_CHECK_EQUAL(sink, "12345");

    sink.erase();

    missio::format::write(sink, missio::format::upper(false));
    BOOST_CHECK_EQUAL(sink, "FALSE");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::upper("abcde"));
    BOOST_CHECK_EQUAL(sink, "ABCDE");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::upper(12345));
    BOOST_CHECK_EQUAL(sink, "12345");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::upper(false));
    BOOST_CHECK_EQUAL(sink, "FALSE");
}

BOOST_AUTO_TEST_CASE(lower_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::lower("ABCDE"));
    BOOST_CHECK_EQUAL(sink, "abcde");

    sink.erase();

    missio::format::write(sink, missio::format::lower(12345));
    BOOST_CHECK_EQUAL(sink, "12345");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::lower("ABCDE"));
    BOOST_CHECK_EQUAL(sink, "abcde");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::lower(12345));
    BOOST_CHECK_EQUAL(sink, "12345");
}

BOOST_AUTO_TEST_CASE(decimal_precision_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::dec(42, 6));
    BOOST_CHECK_EQUAL(sink, "000042");

    sink.erase();

    missio::format::write(sink, missio::format::dec(-42, 6));
    BOOST_CHECK_EQUAL(sink, "-000042");

    sink.erase();

    missio::format::write(sink, missio::format::fixed(1.5, 8));
    BOOST_CHECK_EQUAL(sink, "1.50000000");

    sink.erase();

    missio::format::write(sink, missio::format::fixed(-1.5, 8));
    BOOST_CHECK_EQUAL(sink, "-1.50000000");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::dec(42, 6));
    BOOST_CHECK_EQUAL(sink, "000042");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::dec(-42, 6));
    BOOST_CHECK_EQUAL(sink, "-000042");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::fixed(1.5, 8));
    BOOST_CHECK_EQUAL(sink, "1.50000000");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::fixed(-1.5, 8));
    BOOST_CHECK_EQUAL(sink, "-1.50000000");
}

BOOST_AUTO_TEST_CASE(bin_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::bin(123456));
    BOOST_CHECK_EQUAL(sink, "11110001001000000");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::bin(123456));
    BOOST_CHECK_EQUAL(sink, "11110001001000000");
}

BOOST_AUTO_TEST_CASE(oct_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::oct(987654));
    BOOST_CHECK_EQUAL(sink, "3611006");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::oct(987654));
    BOOST_CHECK_EQUAL(sink, "3611006");
}

BOOST_AUTO_TEST_CASE(hex_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::hex(20526534579951LL));
    BOOST_CHECK_EQUAL(sink, "12ab34cd56ef");

    sink.erase();

    missio::format::write(sink, missio::format::hex(20526534579951LL, 0, true));
    BOOST_CHECK_EQUAL(sink, "12AB34CD56EF");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::hex(20526534579951LL));
    BOOST_CHECK_EQUAL(sink, "12ab34cd56ef");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::hex(20526534579951LL, 0, true));
    BOOST_CHECK_EQUAL(sink, "12AB34CD56EF");
}

BOOST_AUTO_TEST_CASE(decimal_sign_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::dec(1, 0, true));
    BOOST_CHECK_EQUAL(sink, "+1");

    sink.erase();

    missio::format::write(sink, missio::format::dec(-1, 0, true));
    BOOST_CHECK_EQUAL(sink, "-1");

    sink.erase();

    missio::format::write(sink, missio::format::dec(0, 0, true));
    BOOST_CHECK_EQUAL(sink, " 0");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::dec(1, 0, true));
    BOOST_CHECK_EQUAL(sink, "+1");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::dec(-1, 0, true));
    BOOST_CHECK_EQUAL(sink, "-1");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::dec(0, 0, true));
    BOOST_CHECK_EQUAL(sink, " 0");
}

BOOST_AUTO_TEST_CASE(real_sign_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::fixed(1.0, -1, true));
    BOOST_CHECK_EQUAL(sink, "+1.0");

    sink.erase();

    missio::format::write(sink, missio::format::fixed(-1.0, -1, true));
    BOOST_CHECK_EQUAL(sink, "-1.0");

    sink.erase();

    missio::format::write(sink, missio::format::fixed(0.0, -1, true));
    BOOST_CHECK_EQUAL(sink, "0.0");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::fixed(1.0, -1, true));
    BOOST_CHECK_EQUAL(sink, "+1.0");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::fixed(-1.0, -1, true));
    BOOST_CHECK_EQUAL(sink, "-1.0");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::fixed(0.0, -1, true));
    BOOST_CHECK_EQUAL(sink, "0.0");
}

BOOST_AUTO_TEST_CASE(combined_modifiers_test)
{
    std::string sink;

    missio::format::write(sink, missio::format::upper(missio::format::hex(20526534579951LL)));
    BOOST_CHECK_EQUAL(sink, "12AB34CD56EF");

    sink.erase();

    missio::format::write(sink, missio::format::left_align(missio::format::upper("abcde"), 16));
    BOOST_CHECK_EQUAL(sink, "ABCDE           ");

    sink.erase();

    missio::format::write(sink, missio::format::upper(missio::format::upper(true)));
    BOOST_CHECK_EQUAL(sink, "TRUE");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::upper(missio::format::hex(20526534579951LL)));
    BOOST_CHECK_EQUAL(sink, "12AB34CD56EF");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::left_align(missio::format::upper("abcde"), 16));
    BOOST_CHECK_EQUAL(sink, "ABCDE           ");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::upper(missio::format::upper(true)));
    BOOST_CHECK_EQUAL(sink, "TRUE");
}

BOOST_AUTO_TEST_SUITE_END()
