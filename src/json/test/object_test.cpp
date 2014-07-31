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


BOOST_AUTO_TEST_SUITE(json_object_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    missio::json::object object;

    BOOST_CHECK_EQUAL(object.empty(), true);
    BOOST_CHECK_EQUAL(object.size(), 0u);
}

BOOST_AUTO_TEST_CASE(value_type_insert_test)
{
    missio::json::object object;
    missio::json::object::value_type value("key", 15);

    BOOST_CHECK_EQUAL(object.insert(object.begin(), value), true);

    BOOST_CHECK_EQUAL(object.size(), 1u);
    BOOST_CHECK_EQUAL((*object.begin()).first, value.first);
    BOOST_CHECK_EQUAL((*object.begin()).second, value.second);
}

BOOST_AUTO_TEST_CASE(key_value_insert_test)
{
    missio::json::object object;
    missio::json::string key("key");
    missio::json::value value(15);

    BOOST_CHECK_EQUAL(object.insert(key, value), true);
    BOOST_CHECK_EQUAL(object.insert(key, value), false);

    BOOST_CHECK_EQUAL(object.size(), 1u);
    BOOST_CHECK_EQUAL((*object.begin()).first, key);
    BOOST_CHECK_EQUAL((*object.begin()).second, value);
}

BOOST_AUTO_TEST_CASE(find_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    BOOST_CHECK(object.find(key1) == object.end());
    BOOST_CHECK(object.find(key2) == object.end());

    object.insert(key1, value1);
    object.insert(key2, value2);

    missio::json::object::const_iterator it1 = object.find(key1);
    missio::json::object::const_iterator it2 = object.find(key2);

    BOOST_CHECK(it1 != object.end());
    BOOST_CHECK(it2 != object.end());
    BOOST_CHECK(it1 != it2);

    BOOST_CHECK_EQUAL((*it1).first, key1);
    BOOST_CHECK_EQUAL((*it1).second, value1);

    BOOST_CHECK_EQUAL((*it2).first, key2);
    BOOST_CHECK_EQUAL((*it2).second, value2);
}

BOOST_AUTO_TEST_CASE(contains_test)
{
    missio::json::object object;
    missio::json::string key("key");
    missio::json::value value(15);

    BOOST_CHECK_EQUAL(object.contains(key), false);

    object.insert(key, value);

    BOOST_CHECK_EQUAL(object.size(), 1u);
    BOOST_CHECK_EQUAL(object.contains(key), true);
}

BOOST_AUTO_TEST_CASE(iterator_erase_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    object.insert(key1, value1);
    object.insert(key2, value2);

    object.erase(object.begin() + 1);

    BOOST_CHECK_EQUAL(object.size(), 1u);

    object.erase(object.begin());

    BOOST_CHECK_EQUAL(object.empty(), true);
}

BOOST_AUTO_TEST_CASE(key_erase_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    BOOST_CHECK_NO_THROW(object.erase(key1));

    object.insert(key1, value1);
    object.insert(key2, value2);

    object.erase(key1);

    BOOST_CHECK_EQUAL(object.size(), 1u);
    BOOST_CHECK_EQUAL(object.contains(key1), false);
    BOOST_CHECK_EQUAL(object.contains(key2), true);

    object.erase(key2);

    BOOST_CHECK_EQUAL(object.empty(), true);
}

BOOST_AUTO_TEST_CASE(assignment_test)
{
    missio::json::object object1;
    missio::json::object object2;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    object1.insert(key1, value1);
    object1.insert(key2, value2);

    object2 = object1;

    BOOST_CHECK_EQUAL(object2.size(), 2u);
    BOOST_CHECK_EQUAL(object2.contains(key1), true);
    BOOST_CHECK_EQUAL(object2.contains(key2), true);
}

BOOST_AUTO_TEST_CASE(move_assignment_test)
{
    missio::json::object object1;
    missio::json::object object2;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    object1.insert(key1, value1);
    object1.insert(key2, value2);

    object2 = std::move(object1);

    BOOST_CHECK_EQUAL(object1.empty(), true);
    BOOST_CHECK_EQUAL(object2.size(), 2u);
    BOOST_CHECK_EQUAL(object2.contains(key1), true);
    BOOST_CHECK_EQUAL(object2.contains(key2), true);
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    object.insert(key1, value1);
    object.insert(key2, value2);

    object.clear();

    BOOST_CHECK_EQUAL(object.empty(), true);
}

BOOST_AUTO_TEST_CASE(index_operator_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(10);
    missio::json::string key2("key2");
    missio::json::value value2(20);

    object[key1] = value1;

    BOOST_CHECK_EQUAL(object.contains(key1), true);
    BOOST_CHECK_EQUAL(object.size(), 1u);
    BOOST_CHECK_EQUAL(object[key1], value1);

    object[key1] = value2;

    BOOST_CHECK_EQUAL(object.size(), 1u);
    BOOST_CHECK_EQUAL(object[key1], value2);

    object[key2] = value1;

    BOOST_CHECK_EQUAL(object.contains(key1), true);
    BOOST_CHECK_EQUAL(object.contains(key2), true);
    BOOST_CHECK_EQUAL(object.size(), 2u);
    BOOST_CHECK_EQUAL(object[key1], value2);
    BOOST_CHECK_EQUAL(object[key2], value1);
}

BOOST_AUTO_TEST_CASE(const_index_operator_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);
    missio::json::string key3("key3");

    object.insert(key1, value1);
    object.insert(key2, value2);

    missio::json::object const& const_object = object;

    BOOST_CHECK_EQUAL(const_object[key1], value1);
    BOOST_CHECK_EQUAL(const_object[key2], value2);

    BOOST_CHECK_THROW(const_object[key3], missio::json::exception);
}

BOOST_AUTO_TEST_CASE(comparison_operators_test)
{
    missio::json::object object1;
    missio::json::object object2;
    missio::json::string key1("key1");
    missio::json::string key2("key2");

    BOOST_CHECK_EQUAL(object1, object2);
    BOOST_CHECK_GE(object1, object2);
    BOOST_CHECK_LE(object1, object2);

    object1[key1] = 10;
    object1[key2] = 20;

    object2[key1] = 10;
    object2[key2] = 20;

    BOOST_CHECK_EQUAL(object1, object2);
    BOOST_CHECK_GE(object1, object2);
    BOOST_CHECK_LE(object1, object2);

    object1[key1] = 30;

    BOOST_CHECK_NE(object1, object2);
    BOOST_CHECK_GE(object1, object2);
    BOOST_CHECK_GT(object1, object2);

    object2[key1] = 50;

    BOOST_CHECK_NE(object1, object2);
    BOOST_CHECK_LE(object1, object2);
    BOOST_CHECK_LT(object1, object2);
}

BOOST_AUTO_TEST_SUITE_END()
