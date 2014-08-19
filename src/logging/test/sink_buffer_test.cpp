//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/logging/detail/sink_buffer.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(logging_sink_buffer_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    missio::logging::detail::sink_buffer sink;

    BOOST_CHECK_EQUAL(sink.empty(), true);
    BOOST_CHECK_EQUAL(sink.size(), 0u);
    BOOST_CHECK_EQUAL(sink.capacity(), 0u);
    BOOST_CHECK_EQUAL(sink.begin(), sink.end());
}

BOOST_AUTO_TEST_CASE(put_test)
{
    missio::logging::detail::sink_buffer sink;

    sink.put('R');

    BOOST_CHECK_EQUAL(sink.size(), 1u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink.data()[0], 'R');
    BOOST_CHECK_LT(sink.begin(), sink.end());

    sink.put('S');

    BOOST_CHECK_EQUAL(sink.size(), 2u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink.data()[0], 'R');
    BOOST_CHECK_EQUAL(sink.data()[1], 'S');
}

BOOST_AUTO_TEST_CASE(move_constructor_test)
{
    missio::logging::detail::sink_buffer sink1;

    // force memory allocation
    sink1.put('R');

    missio::logging::detail::sink_buffer sink2(std::move(sink1));

    BOOST_CHECK_EQUAL(sink1.size(), 0u);
    BOOST_CHECK_EQUAL(sink1.capacity(), 0u);

    BOOST_CHECK_EQUAL(sink2.size(), 1u);
    BOOST_CHECK_EQUAL(sink2.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink2.data()[0], 'R');
}

BOOST_AUTO_TEST_CASE(move_assignment_operator_test)
{
    missio::logging::detail::sink_buffer sink1;
    missio::logging::detail::sink_buffer sink2;

    // force memory allocation
    sink1.put('R');

    sink2 = std::move(sink1);

    BOOST_CHECK_EQUAL(sink1.size(), 0u);
    BOOST_CHECK_EQUAL(sink1.capacity(), 0u);

    BOOST_CHECK_EQUAL(sink2.size(), 1u);
    BOOST_CHECK_EQUAL(sink2.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink2.data()[0], 'R');

    // check that moved object might be re-used
    sink1.put('S');

    BOOST_CHECK_EQUAL(sink1.size(), 1u);
    BOOST_CHECK_EQUAL(sink1.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink1.data()[0], 'S');
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    missio::logging::detail::sink_buffer sink;

    sink.put('R');
    sink.clear();

    BOOST_CHECK_EQUAL(sink.empty(), true);
    BOOST_CHECK_EQUAL(sink.size(), 0u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);
    BOOST_CHECK_EQUAL(sink.begin(), sink.end());
}

BOOST_AUTO_TEST_CASE(grow_buffer_test)
{
    missio::logging::detail::sink_buffer sink;

    char random[129];

    std::srand(std::time(nullptr));

    for(int i = 0; i < 129; ++i)
        random[i] = char(std::rand() % 255);

    for(int i = 0; i < 128; ++i)
        sink.put(random[i]);

    BOOST_CHECK_EQUAL(sink.size(), 128u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u);

    sink.put(char(random[128]));

    BOOST_CHECK_EQUAL(sink.size(), 129u);
    BOOST_CHECK_EQUAL(sink.capacity(), 128u * 4u);

    BOOST_CHECK_EQUAL_COLLECTIONS(random, random + sizeof(random),
                                  sink.data(), sink.data() + sink.size());
}

BOOST_AUTO_TEST_SUITE_END()
