//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/write.hpp>
#include <missio/format/print.hpp>
#include <missio/format/adapters/std.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>

// STL headers
#include <stdexcept>


BOOST_AUTO_TEST_SUITE(format_std_adapters_test_suite)

struct common_fixture
{
    template <typename T>
    static std::string make_string(T const& value)
    {
        return boost::lexical_cast<std::string>(value);
    }
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
    static std::string make_string(std::error_code const& value)
    {
        return value.message() + " (" + value.category().name() + ':' + common_fixture::make_string(value.value()) + ')';
    }
};

BOOST_FIXTURE_TEST_CASE(exception_test, common_fixture)
{
    std::string sink;

    // exceptions derived from std::exception should be supported as well
    std::runtime_error const runtime_error("runtime error");

    missio::format::write(sink, runtime_error);
    BOOST_CHECK_EQUAL(sink, "runtime error");

    sink.erase();

    missio::format::print(sink, "{0}", runtime_error);
    BOOST_CHECK_EQUAL(sink, "runtime error");
}

BOOST_FIXTURE_TEST_CASE(shared_ptr_test, smart_ptr_fixture)
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

BOOST_FIXTURE_TEST_CASE(weak_ptr_test, smart_ptr_fixture)
{
  //TODO: implement!
}

BOOST_FIXTURE_TEST_CASE(error_code_test, system_fixture)
{
    std::error_code const error_code = std::make_error_code(std::errc::bad_address);

    std::string sink;

    missio::format::write(sink, error_code);
    BOOST_CHECK_EQUAL(sink, make_string(error_code));

    sink.erase();

    missio::format::print(sink, "{0}", error_code);
    BOOST_CHECK_EQUAL(sink, make_string(error_code));
}

BOOST_AUTO_TEST_CASE(chrono_duration_test)
{
    auto const duration = std::chrono::hours(33) +
                          std::chrono::minutes(17) +
                          std::chrono::seconds(24) +
                          std::chrono::milliseconds(397);

    std::string sink;

    missio::format::write(sink, duration);
    BOOST_CHECK_EQUAL(sink, "1d 9h 17m 24s 397ms");

    sink.erase();

    missio::format::print(sink, "{0}", duration);
    BOOST_CHECK_EQUAL(sink, "1d 9h 17m 24s 397ms");

    //TODO: add more test cases
}

BOOST_AUTO_TEST_CASE(chrono_time_point_test)
{
  //TODO: implement!
}

BOOST_AUTO_TEST_CASE(pair_test)
{
    std::string sink;

    missio::format::write(sink, std::make_pair("string", 42));
    BOOST_CHECK_EQUAL(sink, "(string, 42)");

    sink.erase();

    missio::format::print(sink, "{0}", std::make_pair("string", 42));
    BOOST_CHECK_EQUAL(sink, "(string, 42)");
}

BOOST_AUTO_TEST_CASE(tuple_test)
{
    std::string sink;

    missio::format::write(sink, std::make_tuple("string", 42, true));
    BOOST_CHECK_EQUAL(sink, "(string, 42, true)");

    sink.erase();

    missio::format::write(sink, std::make_tuple());
    BOOST_CHECK_EQUAL(sink, "()");

    sink.erase();

    missio::format::print(sink, "{0}", std::make_tuple("string", 42, true));
    BOOST_CHECK_EQUAL(sink, "(string, 42, true)");

    sink.erase();

    missio::format::print(sink, "{0}", std::make_tuple());
    BOOST_CHECK_EQUAL(sink, "()");
}

BOOST_AUTO_TEST_SUITE_END()
