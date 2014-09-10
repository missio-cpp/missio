//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/json.hpp>
#include <missio/json/adapters/boost.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/uuid/random_generator.hpp>


BOOST_AUTO_TEST_SUITE(json_adapters_test_suite)

BOOST_AUTO_TEST_CASE(boost_asio_ip_address_test)
{
    boost::asio::ip::address address = boost::asio::ip::address::from_string("192.168.1.1");

    missio::json::value value = address;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "192.168.1.1");
    BOOST_CHECK_EQUAL(value.get<boost::asio::ip::address>(), address);
}

BOOST_AUTO_TEST_CASE(boost_date_time_date_test)
{
    boost::gregorian::date date(2011, 12, 6);

    missio::json::value value = date;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "2011-12-06");
    BOOST_CHECK_EQUAL(value.get<boost::gregorian::date>(), date);
}

BOOST_AUTO_TEST_CASE(boost_date_time_time_duration_test)
{
    boost::posix_time::time_duration duration(18, 35, 43, 123456);

    missio::json::value value = duration;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "18:35:43.123456");
    BOOST_CHECK_EQUAL(value.get<boost::posix_time::time_duration>(), duration);
}

BOOST_AUTO_TEST_CASE(boost_date_time_ptime_test)
{
    boost::gregorian::date date(2011, 12, 6);
    boost::posix_time::time_duration duration(18, 35, 43, 123456);
    boost::posix_time::ptime time(date, duration);

    missio::json::value value = time;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "2011-12-06T18:35:43.123456");
    BOOST_CHECK_EQUAL(value.get<boost::posix_time::ptime>(), time);
}

BOOST_AUTO_TEST_CASE(boost_filesystem_path_test)
{
    boost::filesystem::path filename("/home/user/file.ext");

    missio::json::value value = filename;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "/home/user/file.ext");
    BOOST_CHECK_EQUAL(value.get<boost::filesystem::path>(), filename);
}

BOOST_AUTO_TEST_CASE(boost_uuid_uuid_test)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    missio::json::string string = boost::uuids::to_string(uuid);

    missio::json::value value = uuid;

    BOOST_CHECK_EQUAL(value.is<missio::json::string>(), true);
    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), string);
    BOOST_CHECK_EQUAL(value.get<boost::uuids::uuid>(), uuid);
}

BOOST_AUTO_TEST_SUITE_END()
