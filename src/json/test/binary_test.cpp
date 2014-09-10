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
    binary_fixture() :
        base64_string{ "Zm9vYmFy" },
        binary_data{ 'f', 'o', 'o', 'b', 'a', 'r' }
    {
    }

    std::string const base64_string;
    std::vector<std::uint8_t> const binary_data;
};

BOOST_AUTO_TEST_CASE(default_constructor_test)
{
    missio::json::binary binary;

    BOOST_CHECK_EQUAL(binary.empty(), true);
    BOOST_CHECK_EQUAL(binary.size(), 0u);
}

BOOST_AUTO_TEST_CASE(construct_from_initializer_list_test)
{
    missio::json::binary binary { 'f', 'o', 'o', 'b', 'a', 'r' };

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL(binary.data()[0], std::uint8_t('f'));
    BOOST_CHECK_EQUAL(binary.data()[1], std::uint8_t('o'));
    BOOST_CHECK_EQUAL(binary.data()[2], std::uint8_t('o'));
    BOOST_CHECK_EQUAL(binary.data()[3], std::uint8_t('b'));
    BOOST_CHECK_EQUAL(binary.data()[4], std::uint8_t('a'));
    BOOST_CHECK_EQUAL(binary.data()[5], std::uint8_t('r'));
}

BOOST_AUTO_TEST_CASE(constuct_from_char_array)
{
    char array[6] { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary(array, 6);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), std::begin(array), std::end(array));
}

BOOST_AUTO_TEST_CASE(construct_from_array_test)
{
    std::array<char, 6> array { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary { array };

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), array.begin(), array.end());
}

BOOST_AUTO_TEST_CASE(construct_from_vector_test)
{
    std::vector<char> vector { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary { vector };

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), vector.begin(), vector.end());
}

BOOST_AUTO_TEST_CASE(construct_from_deque_test)
{
    std::deque<char> deque { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary { deque };

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), deque.begin(), deque.end());
}

BOOST_AUTO_TEST_CASE(construct_from_list_test)
{
    std::list<char> list { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary { list };

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), list.begin(), list.end());
}

BOOST_AUTO_TEST_CASE(move_construct_from_vector_test)
{
    std::vector<char> vector { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary { std::vector<char>(vector) };

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), vector.begin(), vector.end());
}

BOOST_FIXTURE_TEST_CASE(move_constructor_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2(std::move(binary1));

    BOOST_CHECK_EQUAL(binary1.empty(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.begin(), binary2.end(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(copy_constructor_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2(binary1);

    BOOST_CHECK_EQUAL_COLLECTIONS(binary1.begin(), binary1.end(), std::begin(binary_data), std::end(binary_data));
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.begin(), binary2.end(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(move_assignment_operator_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2;

    binary2 = std::move(binary1);

    BOOST_CHECK_EQUAL(binary1.empty(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.begin(), binary2.end(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(assignment_operator_test, binary_fixture)
{
    missio::json::binary binary1(binary_data);
    missio::json::binary binary2;

    binary2 = binary1;

    BOOST_CHECK_EQUAL_COLLECTIONS(binary1.begin(), binary1.end(), std::begin(binary_data), std::end(binary_data));
    BOOST_CHECK_EQUAL_COLLECTIONS(binary2.begin(), binary2.end(), std::begin(binary_data), std::end(binary_data));
}

BOOST_FIXTURE_TEST_CASE(clear_test, binary_fixture)
{
    missio::json::binary binary(binary_data);

    binary.clear();

    BOOST_CHECK_EQUAL(binary.empty(), true);
    BOOST_CHECK_EQUAL(binary.size(), 0u);
}

BOOST_AUTO_TEST_CASE(assign_from_initializer_list_test)
{
    missio::json::binary binary;

    binary.assign({ 'f', 'o', 'o', 'b', 'a', 'r' });

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL(binary.data()[0], std::uint8_t('f'));
    BOOST_CHECK_EQUAL(binary.data()[1], std::uint8_t('o'));
    BOOST_CHECK_EQUAL(binary.data()[2], std::uint8_t('o'));
    BOOST_CHECK_EQUAL(binary.data()[3], std::uint8_t('b'));
    BOOST_CHECK_EQUAL(binary.data()[4], std::uint8_t('a'));
    BOOST_CHECK_EQUAL(binary.data()[5], std::uint8_t('r'));
}

BOOST_AUTO_TEST_CASE(assign_from_char_array_test)
{
    char array[6] { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.assign(array, 6);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), std::begin(array), std::end(array));
}

BOOST_AUTO_TEST_CASE(assign_from_vector_test)
{
    std::vector<char> vector { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.assign(vector);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), vector.begin(), vector.end());
}

BOOST_AUTO_TEST_CASE(assign_from_deque_test)
{
    std::deque<char> deque { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.assign(deque);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), deque.begin(), deque.end());
}

BOOST_AUTO_TEST_CASE(assign_from_list_test)
{
    std::list<char> list { 'f', 'o', 'o', 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.assign(list);

    BOOST_CHECK_EQUAL(binary.empty(), false);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), list.begin(), list.end());
}

BOOST_AUTO_TEST_CASE(append_from_initializer_list_test)
{
    missio::json::binary binary;

    binary.append({ 'f', 'o', 'o' });
    binary.append({ 'b', 'a', 'r' });

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL(binary.data()[0], std::uint8_t('f'));
    BOOST_CHECK_EQUAL(binary.data()[1], std::uint8_t('o'));
    BOOST_CHECK_EQUAL(binary.data()[2], std::uint8_t('o'));
    BOOST_CHECK_EQUAL(binary.data()[3], std::uint8_t('b'));
    BOOST_CHECK_EQUAL(binary.data()[4], std::uint8_t('a'));
    BOOST_CHECK_EQUAL(binary.data()[5], std::uint8_t('r'));
}

BOOST_AUTO_TEST_CASE(append_from_char_array_test)
{
    char array1[3] { 'f', 'o', 'o' };
    char array2[3] { 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.append(array1, 3);
    binary.append(array2, 3);

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.begin() + 3, std::begin(array1), std::end(array1));
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin() + 3, binary.end(), std::begin(array2), std::end(array2));
}

BOOST_AUTO_TEST_CASE(append_from_vector_test)
{
    std::vector<char> vector1 { 'f', 'o', 'o' };
    std::vector<char> vector2 { 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.append(vector1);
    binary.append(vector2);

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.begin() + 3, vector1.begin(), vector1.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin() + 3, binary.end(), vector2.begin(), vector2.end());
}

BOOST_AUTO_TEST_CASE(append_from_deque_test)
{
    std::deque<char> deque1 { 'f', 'o', 'o' };
    std::deque<char> deque2 { 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.append(deque1);
    binary.append(deque2);

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.begin() + 3, deque1.begin(), deque1.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin() + 3, binary.end(), deque2.begin(), deque2.end());
}

BOOST_AUTO_TEST_CASE(append_from_list_test)
{
    std::list<char> list1 { 'f', 'o', 'o' };
    std::list<char> list2 { 'b', 'a', 'r' };

    missio::json::binary binary;

    binary.append(list1);
    binary.append(list2);

    BOOST_CHECK_EQUAL(binary.size(), 6u);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.begin() + 3, list1.begin(), list1.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin() + 3, binary.end(), list2.begin(), list2.end());
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

    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), std::begin(binary_data), std::end(binary_data));
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

    BOOST_CHECK(value.get<missio::json::binary>() == binary);
    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<std::string>(), base64_string);
}

BOOST_FIXTURE_TEST_CASE(get_from_value_test, binary_fixture)
{
    missio::json::value value(base64_string);
    missio::json::binary binary = value;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL_COLLECTIONS(binary.begin(), binary.end(), std::begin(binary_data), std::end(binary_data));

    missio::json::value invalid_value("not a BASE-64 encoded string");

    BOOST_CHECK_THROW(invalid_value.get<missio::json::binary>(), missio::json::exception);
}

BOOST_AUTO_TEST_SUITE_END()
