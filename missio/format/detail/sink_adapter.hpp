//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_adapter_hpp
#define _missio_format_detail_sink_adapter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_buffer.hpp>
#include <missio/format/detail/sink_writer.hpp>

// STL headers
#include <iostream>
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
class sink_adapter
{
public:
    explicit sink_adapter(Sink& sink) :
        sink_(sink)
    {
    }

    sink_adapter(sink_adapter const&) = default;
    sink_adapter& operator=(sink_adapter const&) = delete;

    ~sink_adapter()
    {
        sink_writer<Sink>::call(sink_, buffer_);
    }

    void put(char ch)
    {
        buffer_.put(ch);
    }

private:
    Sink& sink_;
    sink_buffer buffer_;
};

template <std::size_t N>
class sink_adapter<char[N]>
{
public:
    explicit sink_adapter(char (&sink)[N]) :
        sink_(sink),
        pos_(0)
    {
    }

    sink_adapter(sink_adapter const&) = default;
    sink_adapter& operator=(sink_adapter const&) = delete;

    ~sink_adapter()
    {
        sink_[pos_] = '\0';
    }

    void put(char ch)
    {
        if(pos_ < N - 1)
            sink_[pos_++] = ch;
    }

private:
    char* sink_;
    std::size_t pos_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_adapter_hpp
