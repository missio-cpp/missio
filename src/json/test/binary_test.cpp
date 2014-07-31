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


BOOST_AUTO_TEST_SUITE(json_binary_test_suite)

struct binary_fixture
{
    binary_fixture()
    {
        base64_string = "Zm9vYmFy";
        std::memcpy(binary_data, "foobar", 6);
    }

    std::string const base64_string;
    std::uint8_t const binary_data[6];
};

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
    missio::json::binary binary;

    BOOST_CHECK_EQUAL(binary.empty(), true);
    BOOST_CHECK_EQUAL(binary.size(), 0u);
}

BOOST_FIXTURE_TEST_CASE(data_constructor_test, binary_fixture)
{
    missio::json::binary binary1 { 'f', 'o', 'o', 'b', 'a', 'r' };

    BOOST_CHECK_EQUAL(binary1.empty(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary1.data(), binary1.data() + binary1.size(), std::begin(binary_data), std::end(binary_data));

    missio::json::binary binary2(binary_data.data(), binary_data.size());

    BOOST_CHECK_EQUAL(binary2.empty(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.data(), binary2.data() + binary2.size(), std::begin(binary_data), std::end(binary_data));

    missio::json::binary binary3(binary_data);

    BOOST_CHECK_EQUAL(binary3.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary3.data(), binary3.data() + binary3.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(move_constructor_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2(std::move(binary1));

    BOOST_CHECK_EQUAL(binary1.empty(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.data(), binary2.data() + binary2.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(copy_constructor_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2(binary1);

    BOOST_CHECK_EQUAL_COLLECTIONS(binary1.data(), binary1.data() + binary1.size(), std::begin(binary_data), std::end(binary_data));
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.data(), binary2.data() + binary2.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(move_assignment_operator_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2;

    binary2 = std::move(binary1);

    BOOST_CHECK_EQUAL(binary1.empty(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.data(), binary2.data() + binary2.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(assignment_operator_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2;

    binary2 = binary1;

    BOOST_CHECK_EQUAL_COLLECTIONS(binary1.data(), binary1.data() + binary1.size(), std::begin(binary_data), std::end(binary_data));
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.data(), binary2.data() + binary2.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(clear_test, binary_fixture)
{
    missio::json::binary binary(binary_data);

    binary.clear();

    BOOST_CHECK_EQUAL(binary.empty(), true);
    BOOST_CHECK_EQUAL(binary.size(), 0u);
}

BOOST_FIXTURE_TEST_CASE(assign_test, binary_fixture)
{
    missio::json::binary binary;

    binary.assign(binary_data);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data(), binary.data() + binary.size(), std::begin(binary_data), std::end(binary_data));

    binary.assign(binary_data.data(), binary_data.size());

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data(), binary.data() + binary.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(append_test, binary_fixture)
{
    missio::json::binary binary;

    binary.append(binary_data);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data(), binary.data() + binary.size(), std::begin(binary_data), std::end(binary_data));

    binary.append(binary_data.data(), binary_data.size());

    BOOST_CHECK_EQUAL(binary.size(), 2u * binary_data.size());
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data(), binary.data() + binary.size() / 2, std::begin(binary_data), std::end(binary_data));
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data() + binary.size() / 2, binary.data() + binary.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(comparison_operators_test, binary_fixture)
{
    missio::json::binary binary1;
    missio::json::binary binary2;

    BOOST_CHECK_EQUAL(binary1, binary2);
    BOOST_CHECK_GE(binary1, binary2);
    BOOST_CHECK_LE(binary1, binary2);

    binary1.assign("123", std::strlen("123"));
    binary2.assign("123", std::strlen("123"));

    BOOST_CHECK_EQUAL(binary1, binary2);
    BOOST_CHECK_GE(binary1, binary2);
    BOOST_CHECK_LE(binary1, binary2);

    binary1.append("4", std::strlen("4"));

    BOOST_CHECK_NE(binary1, binary2);
    BOOST_CHECK_GE(binary1, binary2);
    BOOST_CHECK_GT(binary1, binary2);

    binary2.append("5", std::strlen("5"));

    BOOST_CHECK_NE(binary1, binary2);
    BOOST_CHECK_LE(binary1, binary2);
    BOOST_CHECK_LT(binary1, binary2);
}

BOOST_FIXTURE_TEST_CASE(from_base64_string_test, binary_fixture)
{
    missio::json::binary binary;
    missio::json::string string(base64_string);

    binary = missio::json::binary::from_base64_string(string);

    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data(), binary.data() + binary.size(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(to_base64_string_test, binary_fixture)
{
    missio::json::string string;
    missio::json::binary binary(binary_data);

    string = missio::json::binary::to_base64_string(binary);

    BOOST_CHECK_EQUAL(string, base64_string);
}

BOOST_FIXTURE_TEST_CASE(assign_to_value_test, binary_fixture)
{
    missio::json::binary binary(binary_data);
    missio::json::value value = binary;

    BOOST_CHECK(value.as<missio::json::binary>() == binary);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.as<std::string>(), base64_string);
}

BOOST_FIXTURE_TEST_CASE(get_from_value_test, binary_fixture)
{
    missio::json::value value(base64_string);
    missio::json::binary binary = value;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.data(), binary.data() + binary.size(), std::begin(binary_data), std::end(binary_data));

    missio::json::value invalid_value("not a BASE-64 encoded string");

    BOOST_CHECK_THROW(invalid_value.as<missio::json::binary>(), missio::json::exception);
}

BOOST_AUTO_TEST_SUITE_END()
