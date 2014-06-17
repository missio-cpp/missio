//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_writer_hpp
#define _missio_format_detail_sink_writer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_buffer.hpp>

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
struct sink_writer
{
    static void call(Sink& sink, sink_buffer const& buffer)
    {
        sink.write(buffer.data(), buffer.size());
    }
};

template <typename Char, typename Traits>
struct sink_writer<std::basic_string<Char, Traits>>
{
    static void call(std::basic_string<Char, Traits>& sink, sink_buffer const& buffer)
    {
        sink.append(buffer.data(), buffer.size());
    }
};

template <typename Char, typename Traits>
struct sink_writer<std::basic_ostream<Char, Traits>>
{
    static void call(std::basic_ostream<Char, Traits>& sink, sink_buffer const& buffer)
    {
        sink.write(buffer.data(), buffer.size());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_writer_hpp
