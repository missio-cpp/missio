//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/dispatcher.hpp>

// STL headers
#include <functional>
#include <utility>
#include <chrono>


namespace missio
{
namespace logging
{

dispatcher::dispatcher() :
    timer_(io_service_),
    started_(false)
{
}

dispatcher::~dispatcher()
{
    stop();
}

void dispatcher::start()
{
    if(!started_)
    {
        started_ = true;

        messages_.enable();
        start_work_thread();

        start_flush_timer();
        start_io_thread();
    }
}

void dispatcher::stop()
{
    if(started_)
    {
        started_ = false;

        timer_.cancel();
        io_thread_.join();
        io_service_.reset();

        messages_.disable();
        work_thread_.join();

        writers_.clear();
    }
}

void dispatcher::add_writer(writer_base::pointer writer)
{
    if(!started_)
        writers_.push_back(writer);
}

void dispatcher::dispatch_message(message&& message)
{
    messages_.push(std::move(message));
}

void dispatcher::run()
{
    for(;;)
    {
        try
        {
            message const message = messages_.pop();

            for(auto const& writer : writers_)
            {
                writer->write(message);
            }

            if(message.get_severity() <= error)
                throw detail::message_queue_flushed();
        }
        catch(detail::message_queue_flushed const&)
        {
            for(auto const& writer : writers_)
            {
                writer->flush();
            }
        }
        catch(detail::message_queue_disabled const&)
        {
            break;
        }
        catch(...)
        {
        }
    }
}

void dispatcher::start_flush_timer()
{
    timer_.expires_from_now(std::chrono::seconds(5));
    timer_.async_wait(std::bind(&dispatcher::handle_flush, this, std::placeholders::_1));
}

void dispatcher::start_work_thread()
{
    work_thread_ = std::thread(&dispatcher::run, this);
} 

void dispatcher::start_io_thread()
{
    io_thread_ = std::thread(&dispatcher::run_io_service, this);
} 

void dispatcher::run_io_service()
{
    for(;;)
    {
        try
        {
            io_service_.run();
            break;
        }
        catch(...)
        {
        }
    }
}

void dispatcher::handle_flush(boost::system::error_code const& error)
{
    if(!error)
    {
        messages_.flush();
        start_flush_timer();
    }
}

}   // namespace logging
}   // namespace missio
