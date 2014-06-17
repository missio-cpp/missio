//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/print.hpp>
#include <missio/format/exception.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(format_print_test_suite)

BOOST_AUTO_TEST_CASE(basic_format_test)
{
    std::string sink;

    missio::format::print(sink, "");
    BOOST_CHECK_EQUAL(sink, "");

    sink.erase();

    missio::format::print(sink, "simple string");
    BOOST_CHECK_EQUAL(sink, "simple string");

    sink.erase();

    missio::format::print(sink, "this is {{ curly braces }}");
    BOOST_CHECK_EQUAL(sink, "this is { curly braces }");

    sink.erase();

    missio::format::print(sink, "this is a lot {{{{ of curly braces }}}}");
    BOOST_CHECK_EQUAL(sink, "this is a lot {{ of curly braces }}");
}

BOOST_AUTO_TEST_CASE(literal_format_test)
{
    std::string sink;

    char const* literal = "string";
    missio::format::print(sink, "{0}", literal);
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    wchar_t const* wliteral = L"wstring";
    missio::format::print(sink, "{0}", wliteral);
    BOOST_CHECK_EQUAL(sink, "wstring");

    sink.erase();

    char const array[] = "string";
    missio::format::print(sink, "{0}", array);
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    wchar_t const warray[] = L"wstring";
    missio::format::print(sink, "{0}", warray);
    BOOST_CHECK_EQUAL(sink, "wstring");
}

BOOST_AUTO_TEST_CASE(string_format_test)
{
    std::string sink;

    std::string string = "string";
    missio::format::print(sink, "{0}", string);
    BOOST_CHECK_EQUAL(sink, "string");

    sink.erase();

    std::wstring wstring = L"wstring";
    missio::format::print(sink, "{0}", wstring);
    BOOST_CHECK_EQUAL(sink, "wstring");
}

BOOST_AUTO_TEST_CASE(char_format_test)
{
    std::string sink;

    char char_ = 'N';
    missio::format::print(sink, "{0}", char_);
    BOOST_CHECK_EQUAL(sink, "N");

    sink.erase();

    char wchar_ = L'W';
    missio::format::print(sink, "{0}", wchar_);
    BOOST_CHECK_EQUAL(sink, "W");
}

BOOST_AUTO_TEST_CASE(basic_types_format_test)
{
    std::string sink;

    unsigned char uchar_ = 76;
    missio::format::print(sink, "{0}", uchar_);
    BOOST_CHECK_EQUAL(sink, "76");

    sink.erase();

    int int_ = 256;
    missio::format::print(sink, "{0}", int_);
    BOOST_CHECK_EQUAL(sink, "256");

    sink.erase();

    long long long_long = 9223372036854775807LL;
    missio::format::print(sink, "{0}", long_long);
    BOOST_CHECK_EQUAL(sink, "9223372036854775807");

    sink.erase();

    bool bool_ = true;
    missio::format::print(sink, "{0}", bool_);
    BOOST_CHECK_EQUAL(sink, "true");

    sink.erase();

    float float_ = 2.718281f;
    missio::format::print(sink, "{0}", float_);
    BOOST_CHECK_EQUAL(sink, "2.718281");

    sink.erase();

    double double_ = 3.141592;
    missio::format::print(sink, "{0}", double_);
    BOOST_CHECK_EQUAL(sink, "3.141592");
}

BOOST_AUTO_TEST_CASE(simple_floating_point_format_test)
{
    std::string sink;

    double one = 1.0;
    double zero = 0.0;
    double one_tenth = 0.1;

    missio::format::print(sink, "{0}", one);
    BOOST_CHECK_EQUAL(sink, "1.0");

    sink.erase();

    missio::format::print(sink, "{0}", zero);
    BOOST_CHECK_EQUAL(sink, "0.0");

    sink.erase();

    missio::format::print(sink, "{0}", one_tenth);
    BOOST_CHECK_EQUAL(sink, "0.1");

    sink.erase();
}

BOOST_AUTO_TEST_CASE(missing_item_format_test)
{
    std::string sink;

    missio::format::print(sink, "{0}");
    BOOST_CHECK_EQUAL(sink, "");

    sink.erase();

    missio::format::print(sink, "{0}, {1}", "test");
    BOOST_CHECK_EQUAL(sink, "test, ");

    sink.erase();

    missio::format::print(sink, "{0}, {1}, {2}", "test", 1);
    BOOST_CHECK_EQUAL(sink, "test, 1, ");
}

BOOST_AUTO_TEST_CASE(braces_around_item_format_test)
{
    std::string sink;

    missio::format::print(sink, "this is a {{{0}}} in a curly braces", "value");
    BOOST_CHECK_EQUAL(sink, "this is a {value} in a curly braces");

    sink.erase();

    missio::format::print(sink, "this is a {{{{{0}}}}} in a double curly braces", "value");
    BOOST_CHECK_EQUAL(sink, "this is a {{value}} in a double curly braces");
}

BOOST_AUTO_TEST_CASE(invalid_format_test)
{
    std::string sink;

    BOOST_CHECK_THROW(missio::format::print(sink, "{"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{}"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{N"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{0"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{0,"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{0*"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{-1}"), missio::format::exception);
    BOOST_CHECK_THROW(missio::format::print(sink, "{0:}"), missio::format::exception);
}

BOOST_AUTO_TEST_SUITE_END()
