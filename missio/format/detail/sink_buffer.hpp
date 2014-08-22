//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_buffer_hpp
#define _missio_format_detail_sink_buffer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <iostream>
#include <cstddef>


namespace missio
{
namespace format
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
    typedef char const& reference;
    typedef char const& const_reference;

public:
    sink_buffer();
    ~sink_buffer();

    sink_buffer(sink_buffer const&) = delete;
    sink_buffer& operator=(sink_buffer const&) = delete;

    void clear();

    bool full() const;
    bool empty() const;

    size_type size() const;
    size_type capacity() const;

    const_pointer data() const;

    const_iterator begin() const;
    const_iterator end() const;

    void put(value_type ch);

private:
    void grow_buffer();

private:
    char static_buffer_[128];
    size_type capacity_;
    char* buffer_ptr_;
    size_type size_;
};

inline void sink_buffer::put(value_type ch)
{
    buffer_ptr_[size_++] = ch;

    if(full())
        grow_buffer();
}

inline std::ostream& operator<<(std::ostream& os, sink_buffer const& buffer)
{
    os.write(buffer.data(), buffer.size());
    return os;
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_buffer_hpp
