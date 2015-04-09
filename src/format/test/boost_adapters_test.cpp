//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/write.hpp>
#include <missio/format/print.hpp>
#include <missio/format/adapters/boost.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

// BOOST headers
#include <iostream>


BOOST_AUTO_TEST_SUITE(format_boost_adapters_test_suite)

struct common_fixture
{
    template <typename T>
    static std::string make_string(T const& value)
    {
        return boost::lexical_cast<std::string>(value);
    }
};

struct asio_fixture : common_fixture
{
    asio_fixture() :
        address_v4(boost::asio::ip::address::from_string("192.168.1.1")),
        endpoint_v4(boost::asio::ip::address::from_string("10.10.10.1"), 3128),
        address_v6(boost::asio::ip::address::from_string("2001:1db8:11a3:19d7:1f34:8a2e:27a0:765d")),
        endpoint_v6(boost::asio::ip::address::from_string("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d"), 3128)
    {
    }

    boost::asio::ip::address address_v4;
    boost::asio::ip::tcp::endpoint endpoint_v4;
    boost::asio::ip::address address_v6;
    boost::asio::ip::tcp::endpoint endpoint_v6;
};

struct optional_fixture : common_fixture
{
    template <typename T>
    static std::string make_string(boost::optional<T> const& value)
    {
        return value ? common_fixture::make_string(*value) : std::string();
    }

    boost::optional<int> empty_optional;
    boost::optional<int> int_optional{ -42 };
};

struct intrusive_test
{
    inline friend void intrusive_ptr_add_ref(intrusive_test* ptr)
    {
        ++ptr->ref_count;
    }

    inline friend void intrusive_ptr_release(intrusive_test* ptr)
    {
        if(0u == --ptr->ref_count)
            delete ptr;
    }

    std::size_t ref_count{ 0u };
};

std::ostream& operator<<(std::ostream& os, intrusive_test const& /*intrusive_test*/)
{
    os << "intrusive_test";
    return os;
}

struct smart_ptr_fixture : common_fixture
{
    template <typename T>
    static std::string make_string(boost::shared_ptr<T> const& value)
    {
        return value ? common_fixture::make_string(*value) : std::string();
    }

    template <typename T>
    static std::string make_string(boost::intrusive_ptr<T> const& value)
    {
        return value ? common_fixture::make_string(*value) : std::string();
    }

    smart_ptr_fixture() :
        shared_pointer(new int(-42)),
        intrusive_pointer(new intrusive_test)
    {
    }

    boost::shared_ptr<int> shared_pointer;
    boost::shared_ptr<int> empty_shared_pointer;

    boost::intrusive_ptr<intrusive_test> intrusive_pointer;
    boost::intrusive_ptr<intrusive_test> empty_intrusive_pointer;
};

struct system_fixture : common_fixture
{
    static std::string make_string(boost::system::error_code const& value)
    {
        return value.message() + " (" + value.category().name() + ':' + common_fixture::make_string(value.value()) + ')';
    }

    system_fixture() :
        error_code(boost::system::errc::make_error_code(boost::system::errc::bad_address))
    {
    }

    boost::system::error_code error_code;
};

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_address_test, asio_fixture)
{
    std::string sink;

    missio::format::write(sink, address_v4);
    BOOST_CHECK_EQUAL(sink, make_string(address_v4));

    sink.erase();

    missio::format::print(sink, "{0}", address_v4);
    BOOST_CHECK_EQUAL(sink, make_string(address_v4));

    sink.erase();

    missio::format::write(sink, address_v6);
    BOOST_CHECK_EQUAL(sink, make_string(address_v6));

    sink.erase();

    missio::format::print(sink, "{0}", address_v6);
    BOOST_CHECK_EQUAL(sink, make_string(address_v6));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_endpoint_test, asio_fixture)
{
    std::string sink;

    missio::format::write(sink, endpoint_v4);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint_v4));

    sink.erase();

    missio::format::print(sink, "{0}", endpoint_v4);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint_v4));

    sink.erase();

    missio::format::write(sink, endpoint_v6);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint_v6));

    sink.erase();

    missio::format::print(sink, "{0}", endpoint_v6);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint_v6));
}

BOOST_FIXTURE_TEST_CASE(boost_filesystem_path_test, common_fixture)
{
    std::string sink;

    boost::filesystem::path const path = boost::filesystem::current_path();

    missio::format::write(sink, path);
    BOOST_CHECK_EQUAL(sink, make_string(path));

    sink.erase();

    missio::format::print(sink, "{0}", path);
    BOOST_CHECK_EQUAL(sink, make_string(path));
}

BOOST_FIXTURE_TEST_CASE(boost_optional_test, optional_fixture)
{
    std::string sink;

    missio::format::write(sink, empty_optional);
    BOOST_CHECK_EQUAL(sink, make_string(empty_optional));

    sink.erase();

    missio::format::write(sink, int_optional);
    BOOST_CHECK_EQUAL(sink, make_string(int_optional));

    sink.erase();

    missio::format::print(sink, "{0}", empty_optional);
    BOOST_CHECK_EQUAL(sink, make_string(empty_optional));

    sink.erase();

    missio::format::print(sink, "{0}", int_optional);
    BOOST_CHECK_EQUAL(sink, make_string(int_optional));
}

BOOST_FIXTURE_TEST_CASE(boost_intrusive_ptr_test, smart_ptr_fixture)
{
    std::string sink;

    missio::format::write(sink, empty_intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_intrusive_pointer));

    sink.erase();

    missio::format::write(sink, intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(intrusive_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", empty_intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_intrusive_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(intrusive_pointer));
}

BOOST_FIXTURE_TEST_CASE(boost_shared_ptr_test, smart_ptr_fixture)
{
    std::string sink;

    missio::format::write(sink, empty_shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_shared_pointer));

    sink.erase();

    missio::format::write(sink, shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(shared_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", empty_shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_shared_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(shared_pointer));
}

BOOST_FIXTURE_TEST_CASE(boost_system_error_code_test, system_fixture)
{
    std::string sink;

    missio::format::write(sink, error_code);
    BOOST_CHECK_EQUAL(sink, make_string(error_code));

    sink.erase();

    missio::format::print(sink, "{0}", error_code);
    BOOST_CHECK_EQUAL(sink, make_string(error_code));
}

BOOST_FIXTURE_TEST_CASE(boost_uuid_test, common_fixture)
{
    std::string sink;

    boost::uuids::random_generator uuid_generator;
    boost::uuids::uuid const uuid = uuid_generator();

    missio::format::write(sink, uuid);
    BOOST_CHECK_EQUAL(sink, make_string(uuid));

    sink.erase();

    missio::format::print(sink, "{0}", uuid);
    BOOST_CHECK_EQUAL(sink, make_string(uuid));
}

BOOST_AUTO_TEST_SUITE_END()
