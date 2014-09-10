//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/json.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(json_read_test_suite)

BOOST_AUTO_TEST_CASE(empty_array_read_test)
{
    std::string const data = "[]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().empty(), true);
}

BOOST_AUTO_TEST_CASE(empty_object_read_test)
{
    std::string const data = "{}";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::object>().empty(), true);
}

BOOST_AUTO_TEST_CASE(null_read_test)
{
    std::string const data = "[null]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<missio::json::null>(), true);
}

BOOST_AUTO_TEST_CASE(integer_read_test)
{
    std::string const data = "[129]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<int>(), true);
    BOOST_CHECK_EQUAL(value[0].get<int>(), 129);
}

BOOST_AUTO_TEST_CASE(real_read_test)
{
    std::string const data = "[3.141592]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<double>(), true);
    BOOST_CHECK_CLOSE(value[0].get<double>(), 3.141592, 0.000001);
}

BOOST_AUTO_TEST_CASE(boolean_read_test)
{
    std::string const data = "[true,false]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 2u);

    BOOST_CHECK_EQUAL(value[0].is<bool>(), true);
    BOOST_CHECK_EQUAL(value[1].is<bool>(), true);

    BOOST_CHECK_EQUAL(value[0].get<bool>(), true);
    BOOST_CHECK_EQUAL(value[1].get<bool>(), false);
}

BOOST_AUTO_TEST_CASE(string_read_test)
{
    std::string const data = "[\"test\"]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<std::string>(), true);
    BOOST_CHECK_EQUAL(value[0].get<std::string>(), "test");
}

BOOST_AUTO_TEST_CASE(string_with_escapes_read_test)
{
    std::string const data = "[\"\\b\\f\\n\\r\\t\\\"\\\\\"]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<std::string>(), true);
    BOOST_CHECK_EQUAL(value[0].get<std::string>(), "\b\f\n\r\t\"\\");
}

BOOST_AUTO_TEST_CASE(unicode_string_read_test)
{
    std::string const data = "[\"\\u043C\\u0438\\u0440\"]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<std::string>(), true);
    BOOST_CHECK_EQUAL(value[0].get<std::string>(), "\xD0\xBC\xD0\xB8\xD1\x80");
}

BOOST_AUTO_TEST_CASE(utf16_surrogate_pair_string_read_test)
{
    std::string const data = "[\"\\uD834\\uDD1E\"]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 1u);

    BOOST_CHECK_EQUAL(value[0].is<std::string>(), true);
    BOOST_CHECK_EQUAL(value[0].get<std::string>(), "\xF0\x9D\x84\x9E");
}

BOOST_AUTO_TEST_CASE(array_read_test)
{
    std::string const data = "[\"string\",3.141592,true]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 3u);

    BOOST_CHECK_EQUAL(value[0].is<std::string>(), true);
    BOOST_CHECK_EQUAL(value[1].is<double>(), true);
    BOOST_CHECK_EQUAL(value[2].is<bool>(), true);

    BOOST_CHECK_EQUAL(value[0].get<std::string>(), "string");
    BOOST_CHECK_CLOSE(value[1].get<double>(), 3.141592, 0.000001);
    BOOST_CHECK_EQUAL(value[2].get<bool>(), true);
}

BOOST_AUTO_TEST_CASE(object_read_test)
{
    std::string const data = "{\"string\":\"value\",\"integer\":42,\"boolean\":false}";
    missio::json::value const value = missio::json::read(data);
    
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::object>().size(), 3u);

    BOOST_CHECK_EQUAL(value["string"].get<std::string>(), "value");
    BOOST_CHECK_EQUAL(value["integer"].get<int>(), 42);
    BOOST_CHECK_EQUAL(value["boolean"].get<bool>(), false);
}

BOOST_AUTO_TEST_CASE(complex_read_test)
{
    std::string const data = "[{\"key1\":\"value\",\"key2\":true},{\"key\":[123,4.5,null]},42]";
    missio::json::value const value = missio::json::read(data);

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>().size(), 3u);

    BOOST_CHECK_EQUAL(value[0].is<missio::json::object>(), true);
    BOOST_CHECK_EQUAL(value[0].get<missio::json::object>().size(), 2u);

    BOOST_CHECK_EQUAL(value[0]["key1"].is<std::string>(), true);
    BOOST_CHECK_EQUAL(value[0]["key2"].is<bool>(), true);

    BOOST_CHECK_EQUAL(value[0]["key1"].get<std::string>(), "value");
    BOOST_CHECK_EQUAL(value[0]["key2"].get<bool>(), true);

    BOOST_CHECK_EQUAL(value[1].is<missio::json::object>(), true);
    BOOST_CHECK_EQUAL(value[1].get<missio::json::object>().size(), 1u);

    BOOST_CHECK_EQUAL(value[1]["key"].is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value[1]["key"].get<missio::json::array>().size(), 3u);

    BOOST_CHECK_EQUAL(value[1]["key"][0].is<int>(), true);
    BOOST_CHECK_EQUAL(value[1]["key"][1].is<double>(), true);
    BOOST_CHECK_EQUAL(value[1]["key"][2].is<missio::json::null>(), true);

    BOOST_CHECK_EQUAL(value[1]["key"][0].get<int>(), 123);
    BOOST_CHECK_CLOSE(value[1]["key"][1].get<double>(), 4.5, 0.000001);
    BOOST_CHECK_EQUAL(value[1]["key"][2].get<missio::json::null>(), missio::json::null_value);

    BOOST_CHECK_EQUAL(value[2].is<int>(), true);
    BOOST_CHECK_EQUAL(value[2].get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(invalid_read_test)
{
    BOOST_CHECK_THROW(missio::json::read(""), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("null"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("invalid"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[naked value]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"line\nbreak\"]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"extra close\"]]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"unclosed array\""), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"bad value\", truth]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("{\"double colon\":: null}"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[ , \"<-- missing value\"]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"comma after the close\"],"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("{\"illegal expression\": 1 + 2}"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("{\"numbers cannot be hex\": 0x14}"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"illegal backslash escape: \\p\"]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"illegal backslash escape: \017\"]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"dangling UTF-16 surrogate: \\uD834\"]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("[\"malformed UTF-16 character: \\u12K3\"]"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::read("{\"extra value after close\": true} \"value\""), missio::json::exception);
}

BOOST_AUTO_TEST_SUITE_END()
