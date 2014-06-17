//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/format.hpp>
#include <missio/format/adapters/boost.hpp>
#include <missio/format/adapters/pointer.hpp>
#include <missio/format/adapters/exception.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/config.hpp>

// BOOST headers
#include <stdexcept>
#include <iostream>
#include <cmath>


BOOST_AUTO_TEST_SUITE(format_adapters_test_suite)

struct common_fixture
{
    static std::string make_aligned(std::string const& str, int align)
    {
        int const size = static_cast<int>(str.size());
        int const width = std::max(size, std::abs(align));

        if(align > 0)
            return std::string(width - size, ' ').append(str);

        return std::string(str).append(std::string(width - size, ' '));
    }

    template <typename T>
    static std::string make_string(T const& value)
    {
        return boost::lexical_cast<std::string>(value);
    }
};

struct pointer_fixture : common_fixture
{
    pointer_fixture() :
        pointer(reinterpret_cast<void const*>(0x123abc)),
        null_pointer(reinterpret_cast<void const*>(0))
    {
    }

    void const* pointer;
    void const* null_pointer;
};

struct asio_v4_fixture : common_fixture
{
    asio_v4_fixture() :
        address(boost::asio::ip::address::from_string("192.168.1.1")),
        endpoint(boost::asio::ip::address::from_string("10.10.10.1"), 3128)
    {
    }

    boost::asio::ip::address const address;
    boost::asio::ip::tcp::endpoint const endpoint;
};

struct asio_v6_fixture : common_fixture
{
    asio_v6_fixture() :
        address(boost::asio::ip::address::from_string("2001:1db8:11a3:19d7:1f34:8a2e:27a0:765d")),
        endpoint(boost::asio::ip::address::from_string("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d"), 3128)
    {
    }

    boost::asio::ip::address const address;
    boost::asio::ip::tcp::endpoint const endpoint;
};

struct optional_fixture : common_fixture
{
    template <typename T>
    static std::string make_string(boost::optional<T> const& value)
    {
        return (value ? common_fixture::make_string(*value) : std::string(""));
    }

    optional_fixture() :
        int_optional(-42)
    {
    }

    boost::optional<int> const empty_optional;
    boost::optional<int> const int_optional;
};

struct intrusive_test
{
    std::size_t ref_count;

    intrusive_test() :
        ref_count(0)
    {
    }

    inline friend void intrusive_ptr_add_ref(intrusive_test* ptr)
    {
        ++ptr->ref_count;
    }

    inline friend void intrusive_ptr_release(intrusive_test* ptr)
    {
        if(0 == --ptr->ref_count)
            delete ptr;
    }
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
        return (value ? common_fixture::make_string(*value) : std::string(""));
    }

    template <typename T>
    static std::string make_string(boost::intrusive_ptr<T> const& value)
    {
        return (value ? common_fixture::make_string(*value) : std::string(""));
    }

    smart_ptr_fixture() :
        shared_pointer(new int(-42)),
        intrusive_pointer(new intrusive_test)
    {
    }

    boost::shared_ptr<int> const shared_pointer;
    boost::shared_ptr<int> const empty_shared_pointer;

    boost::intrusive_ptr<intrusive_test> const intrusive_pointer;
    boost::intrusive_ptr<intrusive_test> const empty_intrusive_pointer;
};

struct system_fixture : common_fixture
{
    system_fixture() :
        error_code(boost::system::errc::make_error_code(boost::system::errc::bad_address))
    {
    }

    boost::system::error_code const error_code;
};

BOOST_FIXTURE_TEST_CASE(pointer_write_test, pointer_fixture)
{
    std::string sink;

    missio::format::write(sink, pointer);
    BOOST_CHECK_EQUAL(sink, make_string(pointer));

    sink.erase();

    missio::format::write(sink, missio::format::align(pointer, 32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(pointer), 32));

    sink.erase();

    missio::format::write(sink, missio::format::align(pointer, -32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(pointer), -32));
}

BOOST_FIXTURE_TEST_CASE(pointer_print_test, pointer_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", pointer);
    BOOST_CHECK_EQUAL(sink, make_string(pointer));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(pointer, 32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(pointer), 32));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(pointer, -32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(pointer), -32));
}

BOOST_FIXTURE_TEST_CASE(null_pointer_write_test, pointer_fixture)
{
    std::string sink;

    missio::format::write(sink, null_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(null_pointer));

    sink.erase();

    missio::format::write(sink, missio::format::align(null_pointer, 32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(null_pointer), 32));

    sink.erase();

    missio::format::write(sink, missio::format::align(null_pointer, -32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(null_pointer), -32));
}

BOOST_FIXTURE_TEST_CASE(null_pointer_print_test, pointer_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", null_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(null_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(null_pointer, 32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(null_pointer), 32));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(null_pointer, -32));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(null_pointer), -32));
}

BOOST_FIXTURE_TEST_CASE(exception_write_test, common_fixture)
{
    std::string sink;

    // exceptions derived from std::exception should be supported as well
    std::runtime_error const runtime_error("runtime error");

    missio::format::write(sink, runtime_error);
    BOOST_CHECK_EQUAL(sink, "runtime error");

    sink.erase();

    missio::format::write(sink, missio::format::align(runtime_error, 20));
    BOOST_CHECK_EQUAL(sink, make_aligned("runtime error", 20));

    sink.erase();

    missio::format::write(sink, missio::format::align(runtime_error, -20));
    BOOST_CHECK_EQUAL(sink, make_aligned("runtime error", -20));
}

BOOST_FIXTURE_TEST_CASE(exception_print_test, common_fixture)
{
    std::string sink;

    // exceptions derived from std::exception should be supported as well
    std::runtime_error const runtime_error("runtime error");

    missio::format::print(sink, "{0}", runtime_error);
    BOOST_CHECK_EQUAL(sink, "runtime error");

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(runtime_error, 20));
    BOOST_CHECK_EQUAL(sink, make_aligned("runtime error", 20));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(runtime_error, -20));
    BOOST_CHECK_EQUAL(sink, make_aligned("runtime error", -20));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v4_address_write_test, asio_v4_fixture)
{
    std::string sink;

    missio::format::write(sink, address);
    BOOST_CHECK_EQUAL(sink, make_string(address));

    sink.erase();

    missio::format::write(sink, missio::format::align(address, 20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), 20));

    sink.erase();

    missio::format::write(sink, missio::format::align(address, -20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), -20));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v4_address_print_test, asio_v4_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", address);
    BOOST_CHECK_EQUAL(sink, make_string(address));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(address, 20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), 20));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(address, -20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), -20));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v6_address_write_test, asio_v6_fixture)
{
    std::string sink;

    missio::format::write(sink, address);
    BOOST_CHECK_EQUAL(sink, make_string(address));

    sink.erase();

    missio::format::write(sink, missio::format::align(address, 45));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), 45));

    sink.erase();

    missio::format::write(sink, missio::format::align(address, -45));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), -45));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v6_address_print_test, asio_v6_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", address);
    BOOST_CHECK_EQUAL(sink, make_string(address));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(address, 45));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), 45));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(address, -45));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(address), -45));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v4_endpoint_write_test, asio_v4_fixture)
{
    std::string sink;

    missio::format::write(sink, endpoint);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint));

    sink.erase();

    missio::format::write(sink, missio::format::align(endpoint, 35));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), 35));

    sink.erase();

    missio::format::write(sink, missio::format::align(endpoint, -35));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), -35));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v4_endpoint_print_test, asio_v4_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", endpoint);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(endpoint, 35));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), 35));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(endpoint, -35));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), -35));
}
/*
BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v6_endpoint_write_test, asio_v6_fixture)
{
    std::string sink;

    missio::format::write(sink, endpoint);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint));

    sink.erase();

    missio::format::write(sink, missio::format::align(endpoint, 60));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), 60));

    sink.erase();

    missio::format::write(sink, missio::format::align(endpoint, -60));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), -60));
}

BOOST_FIXTURE_TEST_CASE(boost_asio_ip_v6_endpoint_print_test, asio_v6_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", endpoint);
    BOOST_CHECK_EQUAL(sink, make_string(endpoint));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(endpoint, 60));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), 60));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(endpoint, -60));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(endpoint), -60));
}
*/
BOOST_FIXTURE_TEST_CASE(boost_filesystem_path_write_test, common_fixture)
{
    std::string sink;

    boost::filesystem::path const path = boost::filesystem::current_path();

    missio::format::write(sink, path);
    BOOST_CHECK_EQUAL(sink, make_string(path));

    sink.erase();

    missio::format::write(sink, missio::format::align(path, 20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(path), 20));

    sink.erase();

    missio::format::write(sink, missio::format::align(path, -20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(path), -20));
}

BOOST_FIXTURE_TEST_CASE(boost_filesystem_path_print_test, common_fixture)
{
    std::string sink;

    boost::filesystem::path const path = boost::filesystem::current_path();

    missio::format::print(sink, "{0}", path);
    BOOST_CHECK_EQUAL(sink, make_string(path));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(path, 20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(path), 20));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(path, -20));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(path), -20));
}

BOOST_FIXTURE_TEST_CASE(boost_optional_write_test, optional_fixture)
{
    std::string sink;

    missio::format::write(sink, empty_optional);
    BOOST_CHECK_EQUAL(sink, make_string(empty_optional));

    sink.erase();

    missio::format::write(sink, missio::format::align(empty_optional, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_optional), 10));

    sink.erase();

    missio::format::write(sink, missio::format::align(empty_optional, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_optional), -10));

    sink.erase();

    missio::format::write(sink, int_optional);
    BOOST_CHECK_EQUAL(sink, make_string(int_optional));

    sink.erase();

    missio::format::write(sink, missio::format::align(int_optional, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(int_optional), 10));

    sink.erase();

    missio::format::write(sink, missio::format::align(int_optional, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(int_optional), -10));
}

BOOST_FIXTURE_TEST_CASE(boost_optional_print_test, optional_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", empty_optional);
    BOOST_CHECK_EQUAL(sink, make_string(empty_optional));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(empty_optional, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_optional), 10));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(empty_optional, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_optional), -10));

    sink.erase();

    missio::format::print(sink, "{0}", int_optional);
    BOOST_CHECK_EQUAL(sink, make_string(int_optional));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(int_optional, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(int_optional), 10));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(int_optional, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(int_optional), -10));
}

BOOST_FIXTURE_TEST_CASE(boost_intrusive_ptr_write_test, smart_ptr_fixture)
{
    std::string sink;

    missio::format::write(sink, empty_intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_intrusive_pointer));

    sink.erase();

    missio::format::write(sink, missio::format::align(empty_intrusive_pointer, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_intrusive_pointer), 40));

    sink.erase();

    missio::format::write(sink, missio::format::align(empty_intrusive_pointer, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_intrusive_pointer), -40));

    sink.erase();

    missio::format::write(sink, intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(intrusive_pointer));

    sink.erase();

    missio::format::write(sink, missio::format::align(intrusive_pointer, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(intrusive_pointer), 40));

    sink.erase();

    missio::format::write(sink, missio::format::align(intrusive_pointer, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(intrusive_pointer), -40));
}

BOOST_FIXTURE_TEST_CASE(boost_intrusive_ptr_print_test, smart_ptr_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", empty_intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_intrusive_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(empty_intrusive_pointer, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_intrusive_pointer), 40));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(empty_intrusive_pointer, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_intrusive_pointer), -40));

    sink.erase();

    missio::format::print(sink, "{0}", intrusive_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(intrusive_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(intrusive_pointer, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(intrusive_pointer), 40));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(intrusive_pointer, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(intrusive_pointer), -40));
}

BOOST_FIXTURE_TEST_CASE(boost_shared_ptr_write_test, smart_ptr_fixture)
{
    std::string sink;

    missio::format::write(sink, empty_shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_shared_pointer));

    sink.erase();

    missio::format::write(sink, missio::format::align(empty_shared_pointer, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_shared_pointer), 10));

    sink.erase();

    missio::format::write(sink, missio::format::align(empty_shared_pointer, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_shared_pointer), -10));

    sink.erase();

    missio::format::write(sink, shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(shared_pointer));

    sink.erase();

    missio::format::write(sink, missio::format::align(shared_pointer, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(shared_pointer), 10));

    sink.erase();

    missio::format::write(sink, missio::format::align(shared_pointer, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(shared_pointer), -10));
}

BOOST_FIXTURE_TEST_CASE(boost_shared_ptr_print_test, smart_ptr_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", empty_shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(empty_shared_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(empty_shared_pointer, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_shared_pointer), 10));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(empty_shared_pointer, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(empty_shared_pointer), -10));

    sink.erase();

    missio::format::print(sink, "{0}", shared_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(shared_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(shared_pointer, 10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(shared_pointer), 10));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(shared_pointer, -10));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(shared_pointer), -10));
}

BOOST_FIXTURE_TEST_CASE(boost_system_error_code_write_test, system_fixture)
{
    std::string sink;

    missio::format::write(sink, error_code);
    BOOST_CHECK_EQUAL(sink, make_string(error_code));

    sink.erase();

    missio::format::write(sink, missio::format::align(error_code, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(error_code), 40));

    sink.erase();

    missio::format::write(sink, missio::format::align(error_code, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(error_code), -40));
}

BOOST_FIXTURE_TEST_CASE(boost_system_error_code_print_test, system_fixture)
{
    std::string sink;

    missio::format::print(sink, "{0}", error_code);
    BOOST_CHECK_EQUAL(sink, make_string(error_code));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(error_code, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(error_code), 40));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(error_code, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(error_code), -40));
}

BOOST_FIXTURE_TEST_CASE(boost_uuid_write_test, common_fixture)
{
    std::string sink;

    boost::uuids::random_generator uuid_generator;
    boost::uuids::uuid const uuid = uuid_generator();

    missio::format::write(sink, uuid);
    BOOST_CHECK_EQUAL(sink, make_string(uuid));

    sink.erase();

    missio::format::write(sink, missio::format::align(uuid, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(uuid), 40));

    sink.erase();

    missio::format::write(sink, missio::format::align(uuid, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(uuid), -40));
}

BOOST_FIXTURE_TEST_CASE(boost_uuid_print_test, common_fixture)
{
    std::string sink;

    boost::uuids::random_generator uuid_generator;
    boost::uuids::uuid const uuid = uuid_generator();

    missio::format::print(sink, "{0}", uuid);
    BOOST_CHECK_EQUAL(sink, make_string(uuid));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(uuid, 40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(uuid), 40));

    sink.erase();

    missio::format::print(sink, "{0}", missio::format::align(uuid, -40));
    BOOST_CHECK_EQUAL(sink, make_aligned(make_string(uuid), -40));
}

BOOST_AUTO_TEST_SUITE_END()
