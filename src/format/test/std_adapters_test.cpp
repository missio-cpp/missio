//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/format.hpp>
#include <missio/format/adapters/std.hpp>
#include <missio/format/adapters/pointer.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/config.hpp>

// STL headers
#include <stdexcept>
#include <cmath>


BOOST_AUTO_TEST_SUITE(format_std_adapters_test_suite)

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

struct smart_ptr_fixture : common_fixture
{
    template <typename T>
    static std::string make_string(std::shared_ptr<T> const& value)
    {
        return value ? common_fixture::make_string(*value) : std::string();
    }

    template <typename T>
    static std::string make_string(std::unique_ptr<T> const& value)
    {
        return value ? common_fixture::make_string(*value) : std::string();
    }

    smart_ptr_fixture() :
        shared_pointer(new int(-42)),
        unique_pointer(new int(-42))
    {
    }

    std::shared_ptr<int> const shared_pointer;
    std::shared_ptr<int> const empty_shared_pointer;

    std::unique_ptr<int> const unique_pointer;
    std::unique_ptr<int> const empty_unique_pointer;
};

struct system_fixture : common_fixture
{
    system_fixture() :
        error_code(std::make_error_code(std::errc::bad_address))
    {
    }

    std::error_code const error_code;
};

struct chrono_fixture : common_fixture
{
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

BOOST_FIXTURE_TEST_CASE(shared_ptr_write_test, smart_ptr_fixture)
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

BOOST_FIXTURE_TEST_CASE(shared_ptr_print_test, smart_ptr_fixture)
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

BOOST_FIXTURE_TEST_CASE(weak_ptr_write_test, smart_ptr_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(weak_ptr_print_test, smart_ptr_fixture)
{
  //TODO: implement!
}
/*
BOOST_FIXTURE_TEST_CASE(error_code_write_test, system_fixture)
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

BOOST_FIXTURE_TEST_CASE(error_code_print_test, system_fixture)
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
*/
BOOST_FIXTURE_TEST_CASE(chrono_duration_write_test, chrono_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(chrono_duration_print_test, chrono_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(chrono_time_point_write_test, chrono_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(chrono_time_point_print_test, chrono_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(pair_write_test, chrono_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(pair_print_test, chrono_fixture)
{
  //TODO: implement!
}

BOOST_AUTO_TEST_SUITE_END()
