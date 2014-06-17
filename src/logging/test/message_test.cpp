//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/logging/message.hpp>
#include <missio/format/format.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


BOOST_AUTO_TEST_SUITE(logging_message_test_suite)

struct message_fixture
{
    template <typename T>
    static std::string make_string(T const& value)
    {
        return boost::lexical_cast<std::string>(value);
    }

    static std::string make_string(missio::logging::detail::sink_buffer const& value)
    {
        return std::string(value.begin(), value.end());
    }

    message_fixture() :
        error_string("Error message"),
        warning_string("Warning message"),
        location("component", "function", "file", "line"),
        error_message(missio::logging::error, location, error_string),
        warning_message(missio::logging::warning, location, warning_string)
    {
    }

    std::string const error_string;
    std::string const warning_string;
    missio::logging::location location;
    missio::logging::message error_message;
    missio::logging::message warning_message;
    missio::logging::detail::thread_id thread_id;
    missio::logging::detail::process_id process_id;
};

BOOST_FIXTURE_TEST_CASE(constructor_test, message_fixture)
{
    BOOST_CHECK_EQUAL(error_message.severity(), missio::logging::error);
    BOOST_CHECK_EQUAL(warning_message.severity(), missio::logging::warning);
}

BOOST_FIXTURE_TEST_CASE(move_constructor_test, message_fixture)
{
    missio::logging::message message(std::move(error_message));

    BOOST_CHECK_EQUAL(message.severity(), missio::logging::error);
}

BOOST_FIXTURE_TEST_CASE(move_assignment_operator_test, message_fixture)
{
    error_message = std::move(warning_message);

    BOOST_CHECK_EQUAL(error_message.severity(), missio::logging::warning);
}

BOOST_FIXTURE_TEST_CASE(format_test, message_fixture)
{
    std::string sink;

    warning_message.format(sink, "{0}");
    BOOST_CHECK_EQUAL(sink.empty(), false); // cannot retrieve timestamp from the message

    sink.erase();

    warning_message.format(sink, "{1}");
    BOOST_CHECK_EQUAL(sink, missio::logging::to_string(missio::logging::warning));

    sink.erase();

    warning_message.format(sink, "{2}");
    BOOST_CHECK_EQUAL(sink, make_string(process_id.value()));

    sink.erase();

    warning_message.format(sink, "{3}");
    BOOST_CHECK_EQUAL(sink, make_string(thread_id.value()));

    sink.erase();

    warning_message.format(sink, "{4}");
    BOOST_CHECK_EQUAL(sink, location.component());

    sink.erase();

    warning_message.format(sink, "{5}");
    BOOST_CHECK_EQUAL(sink, location.function());

    sink.erase();

    warning_message.format(sink, "{6}");
    BOOST_CHECK_EQUAL(sink, location.file());

    sink.erase();

    warning_message.format(sink, "{7}");
    BOOST_CHECK_EQUAL(sink, location.line());

    sink.erase();

    warning_message.format(sink, "{8}");
    BOOST_CHECK_EQUAL(sink, warning_string);
}

BOOST_AUTO_TEST_SUITE_END()
