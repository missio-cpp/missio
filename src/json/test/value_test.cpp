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


BOOST_AUTO_TEST_SUITE(json_value_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    missio::json::value value1;

    BOOST_CHECK_EQUAL(value1.variant().which(), 0);

    missio::json::null null;
    missio::json::value value2(null);

    BOOST_CHECK_EQUAL(value2.variant().which(), 0);

    missio::json::real real(0.0);
    missio::json::value value3(real);

    BOOST_CHECK_EQUAL(value3.variant().which(), 1);

    missio::json::integer integer(0);
    missio::json::value value4(integer);

    BOOST_CHECK_EQUAL(value4.variant().which(), 2);

    missio::json::boolean boolean(false);
    missio::json::value value5(boolean);

    BOOST_CHECK_EQUAL(value5.variant().which(), 3);

    missio::json::string string;
    missio::json::value value6(string);

    BOOST_CHECK_EQUAL(value6.variant().which(), 4);

    missio::json::array array;
    missio::json::value value7(array);

    BOOST_CHECK_EQUAL(value7.variant().which(), 5);

    missio::json::object object;
    missio::json::value value8(object);

    BOOST_CHECK_EQUAL(value8.variant().which(), 6);
}

BOOST_AUTO_TEST_CASE(move_constructor_test)
{
    missio::json::null null;
    missio::json::value value1(std::move(null));

    BOOST_CHECK_EQUAL(value1.variant().which(), 0);

    missio::json::real real(0.0);
    missio::json::value value2(std::move(real));

    BOOST_CHECK_EQUAL(value2.variant().which(), 1);

    missio::json::integer integer(0);
    missio::json::value value3(std::move(integer));

    BOOST_CHECK_EQUAL(value3.variant().which(), 2);

    missio::json::boolean boolean(false);
    missio::json::value value4(std::move(boolean));

    BOOST_CHECK_EQUAL(value4.variant().which(), 3);

    missio::json::string string("string");
    missio::json::value value5(std::move(string));

    BOOST_CHECK_EQUAL(value5.variant().which(), 4);

    missio::json::array array;
    missio::json::value value6(std::move(array));

    BOOST_CHECK_EQUAL(value6.variant().which(), 5);

    missio::json::object object;
    missio::json::value value7(std::move(object));

    BOOST_CHECK_EQUAL(value7.variant().which(), 6);
}

BOOST_AUTO_TEST_CASE(move_constructor_sanity_test)
{
    missio::json::array array { 1, 2, 3 };
    missio::json::value const* array_front = &array.front();

    missio::json::value value2 = std::move(array);
    BOOST_CHECK_EQUAL(&value2.get_array().front(), array_front);

    missio::json::object object { { "key", "value" } };
    missio::json::object_value const* object_front = &*object.begin();

    missio::json::value value3 = std::move(object);
    BOOST_CHECK_EQUAL(&*value3.get_object().begin(), object_front);
}

BOOST_AUTO_TEST_CASE(construct_with_compatible_types_test)
{
    missio::json::value value1{ float(0.0) };
    BOOST_CHECK_EQUAL(value1.variant().which(), 1);

    missio::json::value value2{ short(0) };
    BOOST_CHECK_EQUAL(value2.variant().which(), 2);

    missio::json::value value3{ std::string{} };
    BOOST_CHECK_EQUAL(value3.variant().which(), 4);

    missio::json::value value4{ std::wstring{} };
    BOOST_CHECK_EQUAL(value4.variant().which(), 4);
}

BOOST_AUTO_TEST_CASE(move_construct_with_compatible_types_test)
{
    std::string string{ "string" };
    char const* old_str = string.c_str();

    missio::json::value value = std::move(string);

    BOOST_CHECK_EQUAL(value.variant().which(), 4);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>().c_str(), old_str);
}

BOOST_AUTO_TEST_CASE(assignment_changes_type_test)
{
    missio::json::value value;

    value = missio::json::real(0.0);
    BOOST_CHECK_EQUAL(value.variant().which(), 1);

    value = missio::json::integer(0);
    BOOST_CHECK_EQUAL(value.variant().which(), 2);

    value = missio::json::boolean(false);
    BOOST_CHECK_EQUAL(value.variant().which(), 3);

    value = missio::json::string();
    BOOST_CHECK_EQUAL(value.variant().which(), 4);

    value = missio::json::array();
    BOOST_CHECK_EQUAL(value.variant().which(), 5);

    value = missio::json::object();
    BOOST_CHECK_EQUAL(value.variant().which(), 6);

    value = missio::json::null();
    BOOST_CHECK_EQUAL(value.variant().which(), 0);
}

BOOST_AUTO_TEST_CASE(is_value_test)
{
    missio::json::value value;
    BOOST_CHECK_EQUAL(value.is_null(), true);

    value = missio::json::real{ 3.14159 };
    BOOST_CHECK_EQUAL(value.is_real(), true);

    value = missio::json::integer{ 42 };
    BOOST_CHECK_EQUAL(value.is_integer(), true);

    value = missio::json::boolean{ true };
    BOOST_CHECK_EQUAL(value.is_boolean(), true);

    value = missio::json::string{ "string" };
    BOOST_CHECK_EQUAL(value.is_string(), true);

    value = missio::json::array { 1, 2, 3 };
    BOOST_CHECK_EQUAL(value.is_array(), true);

    value = missio::json::object { { "key", "value" } };
    BOOST_CHECK_EQUAL(value.is_object(), true);
}

BOOST_AUTO_TEST_CASE(to_array_test)
{
    missio::json::value value;

    value.to_array() = { 1, 2, 3 };
    BOOST_CHECK_EQUAL(value.is_array(), true);

    // subsequent to_array() calls should preserve content
    BOOST_CHECK_EQUAL(value.to_array().size(), 3u);
    BOOST_CHECK_EQUAL(value.to_array()[0], 1);
    BOOST_CHECK_EQUAL(value.to_array()[1], 2);
    BOOST_CHECK_EQUAL(value.to_array()[2], 3);
}

BOOST_AUTO_TEST_CASE(to_object_test)
{
    missio::json::value value;

    value.to_object() = { { "key", "value" } };
    BOOST_CHECK_EQUAL(value.is_object(), true);

    // subsequent to_object() calls should preserve content
    BOOST_CHECK_EQUAL(value.to_object().size(), 1u);
    BOOST_CHECK_EQUAL(value.to_object()["key"], "value");
}

BOOST_AUTO_TEST_CASE(non_reference_type_cast_operator_test)
{
    missio::json::string string { "string" };
    missio::json::object object { { "key", "value" } };
    missio::json::array array { 1, 2, 3 };

    BOOST_CHECK_NO_THROW(missio::json::real value = missio::json::value(3.14159));
    BOOST_CHECK_NO_THROW(missio::json::integer value = missio::json::value(42));
    BOOST_CHECK_NO_THROW(missio::json::boolean value = missio::json::value(true));
    BOOST_CHECK_NO_THROW(missio::json::string value = missio::json::value(string));
    BOOST_CHECK_NO_THROW(missio::json::object value = missio::json::value(object));
    BOOST_CHECK_NO_THROW(missio::json::array value = missio::json::value(array));
}

BOOST_AUTO_TEST_CASE(get_array_test)
{
    missio::json::value value
    {
        missio::json::array { 1, 2, 3 }
    };

    BOOST_CHECK_NO_THROW(value.get_array());
    BOOST_CHECK_THROW(value.get_object(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(get_object_test)
{
    missio::json::value value
    {
        missio::json::object { { "key", "value" } }
    };

    BOOST_CHECK_NO_THROW(value.get_object());
    BOOST_CHECK_THROW(value.get_array(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(index_operator_changes_type_test)
{
    missio::json::value value;

    value[0] = missio::json::null_value;
    BOOST_CHECK_EQUAL(value.variant().which(), 5);

    value["key"] = missio::json::null_value;
    BOOST_CHECK_EQUAL(value.variant().which(), 6);
}

BOOST_AUTO_TEST_CASE(comparison_operators_test)
{
    missio::json::value value1;
    missio::json::value value2;

    BOOST_CHECK_LE(value1, value2);
    BOOST_CHECK_GE(value1, value2);
    BOOST_CHECK_EQUAL(value1, value2);

    value1 = missio::json::integer(1);

    BOOST_CHECK_GE(value1, value2);
    BOOST_CHECK_GT(value1, value2);
    BOOST_CHECK_NE(value1, value2);

    value2 = missio::json::integer(2);

    BOOST_CHECK_LE(value1, value2);
    BOOST_CHECK_LT(value1, value2);
    BOOST_CHECK_NE(value1, value2);
}

BOOST_AUTO_TEST_CASE(null_value_test)
{
    missio::json::value value;  // null is default

    BOOST_CHECK_EQUAL(value.is<missio::json::null>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::null>(), missio::json::null_value);

    // test invalid conversions

    BOOST_CHECK_EQUAL(value.is<int>(), false);
    BOOST_CHECK_EQUAL(value.is<bool>(), false);
    BOOST_CHECK_EQUAL(value.is<double>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), false);

    BOOST_CHECK_THROW(value.get<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(integer_value_test)
{
    missio::json::value value = 42;

    BOOST_CHECK_EQUAL(value.is<char>(), true);
    BOOST_CHECK_EQUAL(value.is<short>(), true);
    BOOST_CHECK_EQUAL(value.is<int>(), true);
    BOOST_CHECK_EQUAL(value.is<long>(), true);
    BOOST_CHECK_EQUAL(value.is<double>(), true);    // convertible
    BOOST_CHECK_EQUAL(value.is<bool>(), true);      // convertible

    BOOST_CHECK_EQUAL(value, 42);

    BOOST_CHECK_EQUAL(value.get<char>(), 42);
    BOOST_CHECK_EQUAL(value.get<short>(), 42);
    BOOST_CHECK_EQUAL(value.get<int>(), 42);
    BOOST_CHECK_EQUAL(value.get<long>(), 42);
    BOOST_CHECK_EQUAL(value.get<double>(), 42.0);
    BOOST_CHECK_EQUAL(value.get<bool>(), true);

    // test invalid conversions

    BOOST_CHECK_EQUAL(value.is<missio::json::null>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), false);

    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

// should be defined in global scope due to C++03 restrictions
enum numbers
{
    zero,
    one,
    two,
    three
};

BOOST_AUTO_TEST_CASE(enum_value_test)
{
    missio::json::value value = two;

    BOOST_CHECK_EQUAL(value.is<char>(), true);
    BOOST_CHECK_EQUAL(value.is<short>(), true);
    BOOST_CHECK_EQUAL(value.is<int>(), true);
    BOOST_CHECK_EQUAL(value.is<long>(), true);
    BOOST_CHECK_EQUAL(value.is<double>(), true);    // convertible
    BOOST_CHECK_EQUAL(value.is<bool>(), true);      // convertible

    BOOST_CHECK_EQUAL(value, 2);

    BOOST_CHECK(value.get<numbers>() == two);
    BOOST_CHECK_EQUAL(value.get<char>(), 2);
    BOOST_CHECK_EQUAL(value.get<short>(), 2);
    BOOST_CHECK_EQUAL(value.get<int>(), 2);
    BOOST_CHECK_EQUAL(value.get<long>(), 2);
    BOOST_CHECK_EQUAL(value.get<double>(), 2.0);
    BOOST_CHECK_EQUAL(value.get<bool>(), true);

    // test invalid conversions

    BOOST_CHECK_EQUAL(value.is<missio::json::null>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), false);

    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(real_value_test)
{
    missio::json::value value = 3.141592;

    BOOST_CHECK_EQUAL(value.is<float>(), true);
    BOOST_CHECK_EQUAL(value.is<double>(), true);
    BOOST_CHECK_EQUAL(value.is<int>(), true);       // convertible
    BOOST_CHECK_EQUAL(value.is<bool>(), true);      // convertible

    BOOST_CHECK_CLOSE(value.get<float>(), 3.141592, 0.000001);
    BOOST_CHECK_EQUAL(value.get<double>(), 3.141592);
    BOOST_CHECK_EQUAL(value.get<int>(), 3);
    BOOST_CHECK_EQUAL(value.get<bool>(), true);

    // test invalid conversions

    BOOST_CHECK_EQUAL(value.is<missio::json::null>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), false);

    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(boolean_value_test)
{
    missio::json::value value = true;

    BOOST_CHECK_EQUAL(value.is<bool>(), true);
    BOOST_CHECK_EQUAL(value.is<int>(), true);       // convertible
    BOOST_CHECK_EQUAL(value.is<double>(), true);    // convertible

    BOOST_CHECK_EQUAL(value, true);

    BOOST_CHECK_EQUAL(value.get<bool>(), true);
    BOOST_CHECK_EQUAL(value.get<int>(), 1);
    BOOST_CHECK_EQUAL(value.get<double>(), 1.0);

    // test invalid conversions

    BOOST_CHECK_EQUAL(value.is<missio::json::null>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), false);

    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(string_value_test)
{
    missio::json::value value = missio::json::string("string");

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.is<std::string>(), true);
    BOOST_CHECK_EQUAL(value.is<std::wstring>(), true);

    BOOST_CHECK_EQUAL(value, "string");

    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "string");
    BOOST_CHECK_EQUAL(value.get<std::string>(), "string");
    BOOST_CHECK(value.get<std::wstring>() == L"string");

    // test invalid conversions

    BOOST_CHECK_EQUAL(value.is<int>(), false);
    BOOST_CHECK_EQUAL(value.is<bool>(), false);
    BOOST_CHECK_EQUAL(value.is<double>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::null>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), false);
    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), false);

    BOOST_CHECK_THROW(value.get<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(literal_value_test)
{
    missio::json::value value = "ascii";

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.is<std::string>(), true);
    BOOST_CHECK_EQUAL(value.is<std::wstring>(), true);

    BOOST_CHECK_EQUAL(value, "ascii");

    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "ascii");
    BOOST_CHECK_EQUAL(value.get<std::string>(), "ascii");
    BOOST_CHECK(value.get<std::wstring>() == L"ascii");
}

BOOST_AUTO_TEST_CASE(wide_literal_value_test)
{
    missio::json::value value = L"wide";

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.is<std::string>(), true);
    BOOST_CHECK_EQUAL(value.is<std::wstring>(), true);

    BOOST_CHECK_EQUAL(value, "wide");

    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "wide");
    BOOST_CHECK_EQUAL(value.get<std::string>(), "wide");
    BOOST_CHECK(value.get<std::wstring>() == L"wide");
}

BOOST_AUTO_TEST_CASE(array_value_test)
{
    missio::json::value value = missio::json::array();

    BOOST_CHECK_EQUAL(value.is<missio::json::array>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::array>(), missio::json::array{});

    // test invalid conversions

    BOOST_CHECK_THROW(value.get<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(object_value_test)
{
    missio::json::value value = missio::json::object();

    BOOST_CHECK_EQUAL(value.is<missio::json::object>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::object>(), missio::json::object{});

    // test invalid conversions

    BOOST_CHECK_THROW(value.get<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.get<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_SUITE_END()
