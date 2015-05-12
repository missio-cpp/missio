//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/write.hpp>
#include <missio/format/print.hpp>
#include <missio/format/adapters/array.hpp>
#include <missio/format/adapters/pointer.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


BOOST_AUTO_TEST_SUITE(format_adapters_test_suite)

struct common_fixture
{
    template <typename T>
    static std::string make_string(T const& value)
    {
        return boost::lexical_cast<std::string>(value);
    }
};

BOOST_FIXTURE_TEST_CASE(array_test, common_fixture)
{
    int const int_array[] { 1, 2, 3, 4, 5, 6, 7 };
    double const float_array[] { 1.23, 4.56, 7.89 };

    std::string sink;

    missio::format::write(sink, int_array);
    BOOST_CHECK_EQUAL(sink, "[1, 2, 3, 4, 5, 6, 7]");

    sink.erase();

    missio::format::write(sink, float_array);
    BOOST_CHECK_EQUAL(sink, "[1.23, 4.56, 7.89]");
}

BOOST_FIXTURE_TEST_CASE(pointer_test, common_fixture)
{
    void const* pointer = reinterpret_cast<void const*>(0x123abc);
    void const* null_pointer = reinterpret_cast<void const*>(0);

    std::string sink;

    missio::format::write(sink, pointer);
    BOOST_CHECK_EQUAL(sink, "0x123abc");

    sink.erase();

    missio::format::print(sink, "{0}", pointer);
    BOOST_CHECK_EQUAL(sink, "0x123abc");

    sink.erase();

    missio::format::write(sink, null_pointer);
    BOOST_CHECK_EQUAL(sink, "(null)");

    sink.erase();

    missio::format::print(sink, "{0}", null_pointer);
    BOOST_CHECK_EQUAL(sink, "(null)");

    sink.erase();

    missio::format::write(sink, nullptr);
    BOOST_CHECK_EQUAL(sink, "(null)");

    sink.erase();

    missio::format::print(sink, "{0}", nullptr);
    BOOST_CHECK_EQUAL(sink, "(null)");
}

BOOST_FIXTURE_TEST_CASE(array_of_pointers_test, common_fixture)
{
    void const* ptr1 = reinterpret_cast<void const*>(0x123abc);
    void const* ptr2 = reinterpret_cast<void const*>(0x456def);

    void const* ptr_array[] = { ptr1, ptr2, nullptr };

    std::string sink;

    missio::format::write(sink, ptr_array);
    BOOST_CHECK_EQUAL(sink, "[0x123abc, 0x456def, (null)]");

    sink.erase();

    missio::format::print(sink, "{0}", ptr_array);
    BOOST_CHECK_EQUAL(sink, "[0x123abc, 0x456def, (null)]");
}

BOOST_AUTO_TEST_SUITE_END()
