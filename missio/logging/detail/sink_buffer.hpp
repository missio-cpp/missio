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

// STL headers
#include <algorithm>
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
    typedef char value_type;
    typedef std::size_t size_type;
    typedef char const* pointer;
    typedef char const* const_pointer;
    typedef char const* iterator;
    typedef char const* const_iterator;

public:
    sink_buffer();
    ~sink_buffer();

    sink_buffer(sink_buffer const&) = delete;
    sink_buffer& operator=(sink_buffer const&) = delete;

    sink_buffer(sink_buffer&& other);
    sink_buffer& operator=(sink_buffer&& other);

    void clear();

    bool full() const;
    bool empty() const;

    const_pointer data() const;

    const_iterator begin() const;
    const_iterator end() const;

    size_type size() const;
    size_type capacity() const;

    void put(value_type ch);

private:
    void grow_buffer();

private:
    char* buffer_beg_;
    char* buffer_end_;
    char* buffer_pos_;
};

inline void sink_buffer::put(value_type ch)
{
    if(full())
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
        std::copy(std::begin(value), std::end(value), sink_iterator<Sink>(sink));
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
