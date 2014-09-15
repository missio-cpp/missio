//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/sink_buffer.hpp>

// STL headers
#include <cstdlib>
#include <new>


namespace missio
{
namespace logging
{
namespace detail
{

sink_buffer::sink_buffer() :
    buffer_beg_(nullptr),
    buffer_end_(nullptr),
    buffer_pos_(nullptr)
{
}

sink_buffer::~sink_buffer()
{
    std::free(buffer_beg_);
}

sink_buffer::sink_buffer(sink_buffer&& other) :
    buffer_beg_(other.buffer_beg_),
    buffer_end_(other.buffer_end_),
    buffer_pos_(other.buffer_pos_)
{
    other.buffer_beg_ = nullptr;
    other.buffer_end_ = nullptr;
    other.buffer_pos_ = nullptr;
}

sink_buffer& sink_buffer::operator=(sink_buffer&& other)
{
    if(&other != this)
    {
        std::free(buffer_beg_);

        buffer_beg_ = other.buffer_beg_;
        buffer_end_ = other.buffer_end_;
        buffer_pos_ = other.buffer_pos_;

        other.buffer_beg_ = nullptr;
        other.buffer_end_ = nullptr;
        other.buffer_pos_ = nullptr;
    }

    return *this;
}

void sink_buffer::clear()
{
    buffer_pos_ = buffer_beg_;
}

bool sink_buffer::full() const
{
    return buffer_pos_ == buffer_end_;
}

bool sink_buffer::empty() const
{
    return buffer_pos_ == buffer_beg_;
}

sink_buffer::const_pointer sink_buffer::data() const
{
    return buffer_beg_;
}

sink_buffer::const_iterator sink_buffer::begin() const
{
    return buffer_beg_;
}

sink_buffer::const_iterator sink_buffer::end() const
{
    return buffer_pos_;
}

sink_buffer::size_type sink_buffer::size() const
{
    return buffer_pos_ - buffer_beg_;
}

sink_buffer::size_type sink_buffer::capacity() const
{
    return buffer_end_ - buffer_beg_;
}

void sink_buffer::grow_buffer()
{
    size_type const new_capacity = capacity() ? 4u * capacity() : 128u;

    void* buffer = std::realloc(buffer_beg_, new_capacity);

    if(!buffer)
        throw std::bad_alloc();

    size_type const buffer_offset = size();

    buffer_beg_ = static_cast<char*>(buffer);
    buffer_end_ = buffer_beg_ + new_capacity;
    buffer_pos_ = buffer_beg_ + buffer_offset;
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
