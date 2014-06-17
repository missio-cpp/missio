//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/format/sink.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(format_sink_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    missio::format::sink sink;

    BOOST_CHECK(sink.empty());
    BOOST_CHECK_EQUAL(sink.size(), 0u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
}

BOOST_AUTO_TEST_CASE(put_test)
{
    missio::format::sink sink;

    sink.put('R');

    BOOST_CHECK_EQUAL(sink.size(), 1u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink.data()[0], 'R');

    sink.put('S');

    BOOST_CHECK_EQUAL(sink.size(), 2u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink.data()[0], 'R');
    BOOST_CHECK_EQUAL(sink.data()[1], 'S');
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    missio::format::sink sink;

    sink.put('R');
    sink.clear();

    BOOST_CHECK(sink.empty());
    BOOST_CHECK_EQUAL(sink.size(), 0u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
}

BOOST_AUTO_TEST_CASE(grow_buffer_test)
{
    missio::format::sink sink;

    for(int i = 0; i < 127; ++i)
        sink.put(char(i));

    BOOST_CHECK_EQUAL(sink.size(), 127u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);

    sink.put(char(127));

    BOOST_CHECK_EQUAL(sink.size(), 128u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u * 4u);

    for(int i = 0; i < 128; ++i)
        BOOST_CHECK_EQUAL(sink.data()[i], char(i));
}

BOOST_AUTO_TEST_SUITE_END()
