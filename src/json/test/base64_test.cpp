//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/detail/base64.hpp>
#include <missio/json/exception.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(json_base64_test_suite)

struct base64_fixture
{
    static std::vector<unsigned char> make_vector(char const* data)
    {
        return std::vector<unsigned char>(data, data + std::strlen(data));
    }
};

BOOST_FIXTURE_TEST_CASE(encode_test, base64_fixture)
{
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("")), "");
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("f")), "Zg==");
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("fo")), "Zm8=");
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("foo")), "Zm9v");
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("foob")), "Zm9vYg==");
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("fooba")), "Zm9vYmE=");
    BOOST_CHECK_EQUAL(missio::json::detail::base64::encode(make_vector("foobar")), "Zm9vYmFy");
}

BOOST_FIXTURE_TEST_CASE(decode_test, base64_fixture)
{
    BOOST_CHECK(missio::json::detail::base64::decode("") == make_vector(""));
    BOOST_CHECK(missio::json::detail::base64::decode("Zg==") == make_vector("f"));
    BOOST_CHECK(missio::json::detail::base64::decode("Zm8=") == make_vector("fo"));
    BOOST_CHECK(missio::json::detail::base64::decode("Zm9v") == make_vector("foo"));
    BOOST_CHECK(missio::json::detail::base64::decode("Zm9vYg==") == make_vector("foob"));
    BOOST_CHECK(missio::json::detail::base64::decode("Zm9vYmE=") == make_vector("fooba"));
    BOOST_CHECK(missio::json::detail::base64::decode("Zm9vYmFy") == make_vector("foobar"));
}

BOOST_FIXTURE_TEST_CASE(decode_invalid_test, base64_fixture)
{
    BOOST_CHECK_THROW(missio::json::detail::base64::decode("="), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::detail::base64::decode("Z"), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::detail::base64::decode("Zg="), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::detail::base64::decode("Z==="), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::detail::base64::decode("===="), missio::json::exception);
    BOOST_CHECK_THROW(missio::json::detail::base64::decode("Zm9vY*"), missio::json::exception);
}

BOOST_AUTO_TEST_SUITE_END()
