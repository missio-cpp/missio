//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_dispatcher_hpp
#define _missio_logging_dispatcher_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// Application headers
#include <missio/logging/writer_base.hpp>
#include <missio/logging/detail/message_queue.hpp>

// BOOST headers
#include <boost/asio/steady_timer.hpp>

// STL headers
#include <atomic>
#include <thread>
#include <memory>
#include <list>


namespace missio
{
namespace logging
{

class MISSIO_EXPORT dispatcher
{
public:
    dispatcher();
    ~dispatcher();

    dispatcher(dispatcher const&) = delete;
    dispatcher& operator=(dispatcher const&) = delete;

    void start();
    void stop();

    void add_writer(writer_base::pointer writer);

    void dispatch_message(message&& message);

private:
    void run();

    void start_flush_timer();
    void start_work_thread();
    void start_io_thread();
    void run_io_service();

    void handle_flush(boost::system::error_code const& error);

private:
    typedef std::list<writer_base::pointer> writer_list;

private:
    boost::asio::io_service io_service_;
    boost::asio::steady_timer timer_;

    detail::message_queue messages_;

    std::thread work_thread_;
    std::thread io_thread_;

    std::atomic_bool started_;

    writer_list writers_;
};

}   // namespace logging
}   // namespace misio

#endif  // _missio_logging_dispatcher_hpp
