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


BOOST_AUTO_TEST_SUITE(json_array_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    missio::json::array array;

    BOOST_CHECK_EQUAL(array.empty(), true);
    BOOST_CHECK_EQUAL(array.size(), 0u);
}

BOOST_AUTO_TEST_CASE(push_back_test)
{
    missio::json::array array;
    missio::json::value value(15);

    array.push_back(value);

    BOOST_CHECK_EQUAL(array.size(), 1u);
    BOOST_CHECK_EQUAL(array.back(), value);
}

BOOST_AUTO_TEST_CASE(assignment_test)
{
    missio::json::array array1;
    missio::json::array array2;
    missio::json::value value1(1);
    missio::json::value value2(2);

    array1.push_back(value1);
    array1.push_back(value2);

    array2 = array1;

    BOOST_CHECK_EQUAL(array2.size(), 2u);
    BOOST_CHECK_EQUAL(array2.front(), value1);
    BOOST_CHECK_EQUAL(array2.back(), value2);
}

BOOST_AUTO_TEST_CASE(move_assignment_test)
{
    missio::json::array array1;
    missio::json::array array2;
    missio::json::value value1(1);
    missio::json::value value2(2);

    array1.push_back(value1);
    array1.push_back(value2);

    array2 = std::move(array1);

    BOOST_CHECK_EQUAL(array1.empty(), true);
    BOOST_CHECK_EQUAL(array2.size(), 2u);
    BOOST_CHECK_EQUAL(array2.front(), value1);
    BOOST_CHECK_EQUAL(array2.back(), value2);
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    missio::json::array array;
    missio::json::value value;

    array.push_back(value);
    array.push_back(value);

    array.clear();

    BOOST_CHECK_EQUAL(array.empty(), true);
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
    missio::json::array array;
    missio::json::value value1(1);
    missio::json::value value2(2);

    array.push_back(value1);
    array.push_back(value2);

    array.pop_back();

    BOOST_CHECK_EQUAL(array.size(), 1u);
    BOOST_CHECK_EQUAL(array.back(), value1);
}

BOOST_AUTO_TEST_CASE(insert_test)
{
    missio::json::array array;
    missio::json::value value1(1);
    missio::json::value value2(2);
    missio::json::value value3(3);
    missio::json::value value4(4);

    array.push_back(value1);
    array.push_back(value2);

    array.insert(array.begin(), value3);
    array.insert(array.end(), value4);

    BOOST_CHECK_EQUAL(array.size(), 4u);
    BOOST_CHECK_EQUAL(array.front(), value3);
    BOOST_CHECK_EQUAL(array.back(), value4);
}

BOOST_AUTO_TEST_CASE(erase_test)
{
    missio::json::array array;
    missio::json::value value1(1);
    missio::json::value value2(2);
    missio::json::value value3(3);
    missio::json::value value4(4);

    array.push_back(value1);
    array.push_back(value2);
    array.push_back(value3);
    array.push_back(value4);

    array.erase(array.begin());

    BOOST_CHECK_EQUAL(array.size(), 3u);
    BOOST_CHECK_EQUAL(array.front(), value2);

    array.erase(array.begin() + 1, array.end());

    BOOST_CHECK_EQUAL(array.size(), 1u);
    BOOST_CHECK_EQUAL(array.front(), value2);
}

BOOST_AUTO_TEST_CASE(resize_test)
{
    missio::json::array array;
    missio::json::value value;

    array.resize(2);

    BOOST_CHECK_EQUAL(array.size(), 2u);
    BOOST_CHECK_EQUAL(array.front(), value);
    BOOST_CHECK_EQUAL(array.back(), value);
}

BOOST_AUTO_TEST_CASE(grow_test)
{
    missio::json::array array;

    array.grow(2);
    BOOST_CHECK_EQUAL(array.size(), 2u);

    array.grow(1);
    BOOST_CHECK_EQUAL(array.size(), 2u);
}

BOOST_AUTO_TEST_CASE(shrink_test)
{
    missio::json::array array;

    array.resize(4);

    array.shrink(2);
    BOOST_CHECK_EQUAL(array.size(), 2u);

    array.shrink(4);
    BOOST_CHECK_EQUAL(array.size(), 2u);
}

BOOST_AUTO_TEST_CASE(reserve_test)
{
    missio::json::array array;

    array.reserve(4);

    BOOST_CHECK_EQUAL(array.empty(), true);
    BOOST_CHECK_GE(array.capacity(), 4u);
}

BOOST_AUTO_TEST_CASE(index_operator_test)
{
    missio::json::array array;
    missio::json::value value1(10);
    missio::json::value value2(20);

    array[0] = value1;

    BOOST_CHECK_EQUAL(array.size(), 1u);
    BOOST_CHECK_EQUAL(array.front(), value1);

    array[5] = value2;

    BOOST_CHECK_EQUAL(array.size(), 6u);
    BOOST_CHECK_EQUAL(array.front(), value1);
    BOOST_CHECK_EQUAL(array.back(), value2);
}

BOOST_AUTO_TEST_CASE(const_index_operator_test)
{
    missio::json::array array;
    missio::json::value value1(10);
    missio::json::value value2(20);

    array.push_back(value1);
    array.push_back(value2);

    missio::json::array const& const_array = array;

    BOOST_CHECK_EQUAL(const_array[0], value1);
    BOOST_CHECK_EQUAL(const_array[1], value2);

    BOOST_CHECK_THROW(const_array[2], missio::json::exception);
}

BOOST_AUTO_TEST_CASE(comparison_operators_test)
{
    missio::json::array array1;
    missio::json::array array2;

    BOOST_CHECK_EQUAL(array1, array2);
    BOOST_CHECK_GE(array1, array2);
    BOOST_CHECK_LE(array1, array2);

    array1[0] = 10;
    array1[1] = 20;

    array2[0] = 10;
    array2[1] = 20;

    BOOST_CHECK_EQUAL(array1, array2);
    BOOST_CHECK_GE(array1, array2);
    BOOST_CHECK_LE(array1, array2);

    array1[1] = 30;

    BOOST_CHECK_NE(array1, array2);
    BOOST_CHECK_GE(array1, array2);
    BOOST_CHECK_GT(array1, array2);

    array2[1] = 50;

    BOOST_CHECK_NE(array1, array2);
    BOOST_CHECK_LE(array1, array2);
    BOOST_CHECK_LT(array1, array2);
}

BOOST_AUTO_TEST_SUITE_END()
