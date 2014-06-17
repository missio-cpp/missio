//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_sink_buffer_hpp
#define _missio_logging_detail_sink_buffer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/format.hpp>

// BOOST headers
#include <boost/range.hpp>

// STL headers
#include <cstddef>


namespace missio
{
namespace logging
{
namespace detail
{

class sink_buffer
{
public:
    typedef char const* const_iterator;

public:
    sink_buffer();
    ~sink_buffer();

    sink_buffer(sink_buffer const&) = delete;
    sink_buffer& operator=(sink_buffer const&) = delete;

    sink_buffer(sink_buffer&& other);
    sink_buffer& operator=(sink_buffer&& other);

    void clear();
    bool empty() const;

    char const* data() const;

    const_iterator begin() const;
    const_iterator end() const;

    std::size_t size() const;
    std::size_t capacity() const;

    void put(char ch);

private:
    void grow_buffer();

private:
    char* buffer_beg_;
    char* buffer_end_;
    char* buffer_pos_;
};

inline void sink_buffer::put(char ch)
{
    if(buffer_pos_ == buffer_end_)
        grow_buffer();

    *buffer_pos_++ = ch;
}

}   // namespace detail
}   // namespace logging

namespace format
{
namespace detail
{

template <>
struct type_adapter<logging::detail::sink_buffer>
{
    template <typename Sink>
    static void format(Sink& sink, logging::detail::sink_buffer const& value)
    {
         format_value(sink, boost::make_iterator_range(value.begin(), value.end()));
    }
};

}   // namespace detail

namespace traits
{

template <>
struct sink_traits<logging::detail::sink_buffer>
{
    typedef logging::detail::sink_buffer& adapter_type;
}; 

}   // namespace traits
}   // namespace format
}   // namespace missio

#endif  // _missio_logging_detail_sink_buffer_hpp
