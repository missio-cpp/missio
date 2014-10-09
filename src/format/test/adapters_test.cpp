//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/write.hpp>
#include <missio/format/print.hpp>
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

BOOST_FIXTURE_TEST_CASE(pointer_test, pointer_fixture)
{
    std::string sink;

    missio::format::write(sink, pointer);
    BOOST_CHECK_EQUAL(sink, make_string(pointer));

    sink.erase();

    missio::format::print(sink, "{0}", pointer);
    BOOST_CHECK_EQUAL(sink, make_string(pointer));

    sink.erase();

    missio::format::write(sink, null_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(null_pointer));

    sink.erase();

    missio::format::print(sink, "{0}", null_pointer);
    BOOST_CHECK_EQUAL(sink, make_string(null_pointer));
}

BOOST_AUTO_TEST_CASE(array_test)
{
    //TODO: implement!
}

BOOST_AUTO_TEST_SUITE_END()
