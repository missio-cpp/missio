//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/write.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(format_write_test_suite)

BOOST_AUTO_TEST_CASE(literal_write_test)
{
    std::string sink;

    char const* literal = "string";
    missio::format::write(sink, literal);
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    wchar_t const* wliteral = L"wstring";
    missio::format::write(sink, wliteral);
    BOOST_CHECK_EQUAL(sink, "wstring");

    sink.erase();

    char const array[] = "string";
    missio::format::write(sink, array);
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    wchar_t const warray[] = L"wstring";
    missio::format::write(sink, warray);
    BOOST_CHECK_EQUAL(sink, "wstring");
}

BOOST_AUTO_TEST_CASE(string_write_test)
{
    std::string sink;

    std::string string = "string";
    missio::format::write(sink, string);
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    std::wstring wstring = L"wstring";
    missio::format::write(sink, wstring);
    BOOST_CHECK_EQUAL(sink, "wstring");
}

BOOST_AUTO_TEST_CASE(char_write_test)
{
    std::string sink;

    char char_ = 'N';
    missio::format::write(sink, char_);
    BOOST_CHECK_EQUAL(sink, "N");

    sink.erase();

    char wchar_ = L'W';
    missio::format::write(sink, wchar_);
    BOOST_CHECK_EQUAL(sink, "W");
}

BOOST_AUTO_TEST_CASE(basic_types_write_test)
{
    std::string sink;

    unsigned char uchar_ = 76;
    missio::format::write(sink, uchar_);
    BOOST_CHECK_EQUAL(sink, "76");

    sink.erase();

    int int_ = 256;
    missio::format::write(sink, int_);
    BOOST_CHECK_EQUAL(sink, "256");

    sink.erase();

    long long long_long = 9223372036854775807LL;
    missio::format::write(sink, long_long);
    BOOST_CHECK_EQUAL(sink, "9223372036854775807");

    sink.erase();

    bool bool_ = true;
    missio::format::write(sink, bool_);
    BOOST_CHECK_EQUAL(sink, "true");

    sink.erase();

    float float_ = 2.718281f;
    missio::format::write(sink, float_);
    BOOST_CHECK_EQUAL(sink, "2.718281");

    sink.erase();

    double double_ = 3.141592;
    missio::format::write(sink, double_);
    BOOST_CHECK_EQUAL(sink, "3.141592");
}

BOOST_AUTO_TEST_CASE(multi_elements_write_test)
{
    std::string sink;

    missio::format::write(sink, 42, ' ', 3.141592, ' ', true, " hello ", L'!');
    BOOST_CHECK_EQUAL(sink, "42 3.141592 true hello !");
}

BOOST_AUTO_TEST_SUITE_END()
