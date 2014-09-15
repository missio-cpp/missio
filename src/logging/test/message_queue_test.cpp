//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//--------------------------------------------------------------------------- 

// Application headers
#include <missio/logging/detail/message_queue.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>

// STL headers
#include <vector>
#include <thread>

/*
BOOST_AUTO_TEST_SUITE(logging_message_queue_test_suite)

struct common_fixture
{
    common_fixture() :
        info_string("Info string"),
        error_string("Error message"),
        warning_string("Warning message"),
        location("component", "function", "file", "line"),
        info_message(missio::logging::info, location, info_string),
        error_message(missio::logging::error, location, error_string),
        warning_message(missio::logging::warning, location, warning_string)
    {
    }

    std::string const info_string;
    std::string const error_string;
    std::string const warning_string;
    missio::logging::location location;
    missio::logging::message info_message;
    missio::logging::message error_message;
    missio::logging::message warning_message;
    missio::logging::detail::message_queue queue;
};

struct consumer_producer_fixture : common_fixture
{
    consumer_producer_fixture() :
        ready(false),
        total_count(0)
    {
    }

    void wait_ready()
    {
        std::unique_lock<std::mutex> lock(mutex);
        event.wait(lock, [this]{ return ready; });
    }

    void set_ready()
    {
        std::unique_lock<std::mutex> lock(mutex);

        ready = true;

        lock.unlock();
        event.notify_all();
    }

    void produce()
    {
        wait_ready();

        for(int i = 0; i < 10000; ++i)
        {
            queue.push(missio::logging::message(missio::logging::warning, location, warning_string));
        }
    }

    void consume()
    {
        int local_count(0);

        wait_ready();

        for(;;)
        {
            try
            {
                queue.pop();
                ++local_count;
            }
            catch(missio::logging::detail::message_queue_disabled)
            {
                break;
            }
        }

        std::lock_guard<std::mutex> lock(mutex);
        total_count += local_count;
    }

    bool ready;
    int total_count;
    std::mutex mutex;
    std::condition_variable event;
    std::vector<std::thread> producer_threads;
    std::vector<std::thread> consumer_threads;
};

BOOST_FIXTURE_TEST_CASE(message_queue_push_test, common_fixture)
{
    BOOST_CHECK_EQUAL(queue.push(std::move(info_message)), true);
    BOOST_CHECK_EQUAL(queue.push(std::move(error_message)), true);
    BOOST_CHECK_EQUAL(queue.push(std::move(warning_message)), true);
}

BOOST_FIXTURE_TEST_CASE(message_queue_pop_test, common_fixture)
{
    queue.push(std::move(info_message));
    queue.push(std::move(error_message));
    queue.push(std::move(warning_message));

    BOOST_CHECK_NO_THROW(queue.pop());
    BOOST_CHECK_NO_THROW(queue.pop());
    BOOST_CHECK_NO_THROW(queue.pop());
}

BOOST_FIXTURE_TEST_CASE(message_queue_disable_test, common_fixture)
{
    queue.push(std::move(info_message));
    queue.push(std::move(error_message));

    BOOST_CHECK_NO_THROW(queue.pop());

    queue.disable();

    BOOST_CHECK_EQUAL(queue.push(std::move(warning_message)), false);
    BOOST_CHECK_THROW(queue.pop(), missio::logging::detail::message_queue_disabled);
}

BOOST_FIXTURE_TEST_CASE(message_queue_enable_test, common_fixture)
{
    queue.push(std::move(info_message));

    queue.disable();

    BOOST_CHECK_EQUAL(queue.push(std::move(error_message)), false);
    BOOST_CHECK_THROW(queue.pop(), missio::logging::detail::message_queue_disabled);

    queue.enable();

    BOOST_CHECK_EQUAL(queue.push(std::move(warning_message)), true);

    BOOST_CHECK_NO_THROW(queue.pop());
    BOOST_CHECK_NO_THROW(queue.pop());
}

BOOST_FIXTURE_TEST_CASE(message_queue_flush_test, common_fixture)
{
    queue.push(std::move(info_message));
    queue.push(std::move(error_message));

    queue.flush();

    BOOST_CHECK_THROW(queue.pop(), missio::logging::detail::message_queue_flushed);

    BOOST_CHECK_NO_THROW(queue.pop());
    BOOST_CHECK_NO_THROW(queue.pop());
}

BOOST_FIXTURE_TEST_CASE(consumer_producer_test, consumer_producer_fixture)
{
    for(int i = 0; i < 2; ++i)
    {
        producer_threads.emplace_back([this](){ produce(); });
        consumer_threads.emplace_back([this](){ consume(); });
    }

    set_ready();

    for(auto& thread : producer_threads)
    {
        thread.join();
    }

    queue.disable();

    for(auto& thread : consumer_threads)
    {
        thread.join();
    }

    producer_threads.clear();
    consumer_threads.clear();

    BOOST_CHECK_EQUAL(total_count, 20000);
}

BOOST_AUTO_TEST_SUITE_END()
*/