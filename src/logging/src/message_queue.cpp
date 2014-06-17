//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------  

// Application headers
#include <missio/logging/detail/message_queue.hpp>


namespace missio
{
namespace logging
{
namespace detail
{

message_queue::message_queue() :
    enabled_(true),
    flushed_(false)
{
}

message_queue::~message_queue()
{
    disable();
}

void message_queue::enable()
{
    std::unique_lock<std::mutex> lock(mutex_);

    enabled_ = true;
    flushed_ = false;
}

void message_queue::disable()
{
    std::unique_lock<std::mutex> lock(mutex_);

    enabled_ = false;
    flushed_ = false;

    lock.unlock();
    event_.notify_all();
}

bool message_queue::push(message&& message)
{
    std::unique_lock<std::mutex> lock(mutex_);

    if(!enabled_)
        return false;

    messages_.push_back(std::move(message));

    lock.unlock();
    event_.notify_one();

    return true;
}

message message_queue::pop()
{
    std::unique_lock<std::mutex> lock(mutex_);

    while(messages_.empty())
    {
        if(!enabled_)
            throw message_queue_disabled();

        if(flushed_)
        {
            flushed_ = false;
            throw message_queue_flushed();
        }

        event_.wait(lock);
    }

    message message = std::move(messages_.front());
    messages_.pop_front();

    return message;
}

bool message_queue::flush()
{
    std::unique_lock<std::mutex> lock(mutex_);

    if(!enabled_)
        return false;

    flushed_ = true;

    lock.unlock();
    event_.notify_all();

    return true;
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
