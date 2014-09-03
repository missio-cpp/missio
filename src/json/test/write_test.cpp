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


BOOST_AUTO_TEST_SUITE(json_write_test_suite)

BOOST_AUTO_TEST_CASE(default_write_test)
{
    missio::json::value value;  // default is null
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "null");
}

BOOST_AUTO_TEST_CASE(null_write_test)
{
    missio::json::value value = missio::json::null_value;
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "null");
}

BOOST_AUTO_TEST_CASE(integer_write_test)
{
    missio::json::value value = missio::json::integer(32767);
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "32767");
}

BOOST_AUTO_TEST_CASE(real_write_test)
{
    missio::json::value value = missio::json::real(1.618034);
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "1.618034");
}

BOOST_AUTO_TEST_CASE(real_without_fractional_part_write_test)
{
    missio::json::value value = missio::json::real(1);
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "1.0");
}

BOOST_AUTO_TEST_CASE(boolean_write_test)
{
    missio::json::value true_value = missio::json::boolean(true);
    missio::json::value false_value = missio::json::boolean(false);

    std::string true_data = missio::json::write(true_value);
    std::string false_data = missio::json::write(false_value);

    BOOST_CHECK_EQUAL(true_data, "true");
    BOOST_CHECK_EQUAL(false_data, "false");
}

BOOST_AUTO_TEST_CASE(string_write_test)
{
    missio::json::value value = missio::json::string("string");
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "\"string\"");
}

BOOST_AUTO_TEST_CASE(string_with_escapes_write_test)
{
    missio::json::value value = missio::json::string("\b\f\n\r\t\"\\");
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "\"\\b\\f\\n\\r\\t\\\"\\\\\"");
}

BOOST_AUTO_TEST_CASE(string_with_controls_write_test)
{
    missio::json::value value = missio::json::string("\x01\x02\x10");
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "\"\\u0001\\u0002\\u0010\"");
}

BOOST_AUTO_TEST_CASE(utf8_string_write_test)
{
    missio::json::value value = missio::json::string("\xD0\xBC\xD0\xB8\xD1\x80");
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "\"\xD0\xBC\xD0\xB8\xD1\x80\"");
}

BOOST_AUTO_TEST_CASE(empty_array_write_test)
{
    missio::json::value value = missio::json::array();
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "[]");
}

BOOST_AUTO_TEST_CASE(empty_object_write_test)
{
    missio::json::value value = missio::json::object();
    std::string data = missio::json::write(value);

    BOOST_CHECK_EQUAL(data, "{}");
}

BOOST_AUTO_TEST_CASE(array_write_test)
{
    missio::json::array value;

    value[0] = 42;
    value[1] = true;
    value[2] = "test";

    std::string data = missio::json::write(value);
    BOOST_CHECK_EQUAL(data, "[42,true,\"test\"]");
}

BOOST_AUTO_TEST_CASE(object_write_test)
{
    missio::json::object value;

    value["key1"] = 42;
    value["key2"] = true;
    value["key3"] = "test";

    std::string data = missio::json::write(value);
    BOOST_CHECK_EQUAL(data, "{\"key1\":42,\"key2\":true,\"key3\":\"test\"}");
}

BOOST_AUTO_TEST_CASE(complex_write_test)
{
    missio::json::array value;

    value[0]["key1"] = "value";
    value[0]["key2"] = true;

    value[1]["key"][0] = 123;
    value[1]["key"][1] = 4.5;
    value[1]["key"][2] = missio::json::null_value;

    value[2] = 42;

    std::string data = missio::json::write(value);
    BOOST_CHECK_EQUAL(data, "[{\"key1\":\"value\",\"key2\":true},{\"key\":[123,4.5,null]},42]");
}

BOOST_AUTO_TEST_SUITE_END()
