//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------  
#ifndef _missio_logging_detail_message_queue_hpp
#define _missio_logging_detail_message_queue_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/message.hpp>

// STL headers
#include <condition_variable>
#include <mutex>
#include <utility>
#include <deque>


namespace missio
{
namespace logging
{
namespace detail
{

struct message_queue_flushed {};
struct message_queue_disabled {};

class message_queue
{
public:
    message_queue();
    ~message_queue();

    message_queue(message_queue const&) = delete;
    message_queue& operator=(message_queue const&) = delete;

    void enable();
    void disable();

    bool push(message&& message);

    message pop();

    bool flush();

private:
    bool enabled_;
    bool flushed_;

    std::deque<message> messages_;

    std::mutex mutex_;
    std::condition_variable event_;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_message_queue_hpp
