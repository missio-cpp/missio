//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/json.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(json_reference_test_suite)

BOOST_AUTO_TEST_CASE(array_constructor_test)
{
    missio::json::array array;
    missio::json::value value(15);

    array.push_back(value);

    missio::json::array_ref array_ref(array);
    missio::json::array_cref array_cref(array);

    BOOST_CHECK_EQUAL(array_ref->size(), 1u);
    BOOST_CHECK_EQUAL(array_ref->back(), value);

    BOOST_CHECK_EQUAL(array_cref->size(), 1u);
    BOOST_CHECK_EQUAL(array_cref->back(), value);

    missio::json::array_cref other_array_cref(array_ref);

    BOOST_CHECK_EQUAL(other_array_cref->size(), 1u);
    BOOST_CHECK_EQUAL(other_array_cref->back(), value);

    BOOST_CHECK_THROW((missio::json::array_cref)(value), missio::json::exception);

    BOOST_CHECK_NO_THROW((missio::json::array_ref)(value));
    BOOST_CHECK(value.is<missio::json::array>());
}

BOOST_AUTO_TEST_CASE(object_constructor_test)
{
    missio::json::object object;
    missio::json::string key("key1");
    missio::json::value value(1);

    object.insert(key, value);

    missio::json::object_ref object_ref(object);
    missio::json::object_cref object_cref(object);

    BOOST_CHECK_EQUAL(object_ref->size(), 1u);
    BOOST_CHECK(object_ref->contains(key));

    BOOST_CHECK_EQUAL(object_cref->size(), 1u);
    BOOST_CHECK(object_ref->contains(key));

    missio::json::object_cref other_object_cref(object_ref);

    BOOST_CHECK_EQUAL(other_object_cref->size(), 1u);
    BOOST_CHECK(other_object_cref->contains(key));

    BOOST_CHECK_THROW((missio::json::object_cref)(value), missio::json::exception);

    BOOST_CHECK_NO_THROW((missio::json::object_ref)(value));
    BOOST_CHECK(value.is<missio::json::object>());
}

BOOST_AUTO_TEST_CASE(array_reference_test)
{
    missio::json::array array;
    missio::json::value value1(1);
    missio::json::value value2(2);

    missio::json::array_ref array_ref(array);

    array_ref[0] = value1;
    array_ref[1] = value2;

    BOOST_CHECK_EQUAL(array.size(), 2u);
    BOOST_CHECK_EQUAL(array[0], value1);
    BOOST_CHECK_EQUAL(array[1], value2);

    missio::json::value const value = array_ref;

    BOOST_CHECK(value.is<missio::json::array>());
    BOOST_CHECK_EQUAL(value[0], value1);
    BOOST_CHECK_EQUAL(value[1], value2);
}

BOOST_AUTO_TEST_CASE(array_const_reference_test)
{
    missio::json::array array;
    missio::json::value value1(1);
    missio::json::value value2(2);

    missio::json::array_cref array_cref(array);

    BOOST_CHECK_EQUAL(array_cref->size(), 0u);
    BOOST_CHECK_THROW(array_cref[0], missio::json::exception);
    BOOST_CHECK_THROW(array_cref[1], missio::json::exception);

    array[0] = value1;
    array[1] = value2;

    BOOST_CHECK_EQUAL(array_cref->size(), 2u);
    BOOST_CHECK_EQUAL(array_cref[0], value1);
    BOOST_CHECK_EQUAL(array_cref[1], value2);

    missio::json::value const value = array_cref;

    BOOST_CHECK(value.is<missio::json::array>());
    BOOST_CHECK_EQUAL(value[0], value1);
    BOOST_CHECK_EQUAL(value[1], value2);
}

BOOST_AUTO_TEST_CASE(object_reference_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    missio::json::object_ref object_ref(object);

    object_ref[key1] = value1;
    object_ref[key2] = value2;

    BOOST_CHECK(object.contains(key1));
    BOOST_CHECK(object.contains(key2));
    BOOST_CHECK_EQUAL(object[key1], value1);
    BOOST_CHECK_EQUAL(object[key2], value2);

    missio::json::value const value = object_ref;

    BOOST_CHECK(value.is<missio::json::object>());
    BOOST_CHECK_EQUAL(value[key1], value1);
    BOOST_CHECK_EQUAL(value[key2], value2);
}

BOOST_AUTO_TEST_CASE(object_const_reference_test)
{
    missio::json::object object;
    missio::json::string key1("key1");
    missio::json::value value1(1);
    missio::json::string key2("key2");
    missio::json::value value2(2);

    missio::json::object_cref object_cref(object);

    BOOST_CHECK(!object_cref->contains(key1));
    BOOST_CHECK(!object_cref->contains(key2));
    BOOST_CHECK_THROW(object_cref[key1], missio::json::exception);
    BOOST_CHECK_THROW(object_cref[key2], missio::json::exception);

    object[key1] = value1;
    object[key2] = value2;

    BOOST_CHECK(object_cref->contains(key1));
    BOOST_CHECK(object_cref->contains(key2));
    BOOST_CHECK_EQUAL(object_cref[key1], value1);
    BOOST_CHECK_EQUAL(object_cref[key2], value2);

    missio::json::value const value = object_cref;

    BOOST_CHECK(value.is<missio::json::object>());
    BOOST_CHECK_EQUAL(value[key1], value1);
    BOOST_CHECK_EQUAL(value[key2], value2);
}

BOOST_AUTO_TEST_SUITE_END()
