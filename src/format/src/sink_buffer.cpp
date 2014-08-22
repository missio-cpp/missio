//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/detail/sink_buffer.hpp>

// STL headers
#include <cstring>
#include <cstdlib>
#include <new>


namespace missio
{
namespace format
{
namespace detail
{

sink_buffer::sink_buffer() :
    capacity_(sizeof(static_buffer_)),
    buffer_ptr_(static_buffer_),
    size_(0u)
{
}

sink_buffer::~sink_buffer()
{
    if(buffer_ptr_ != static_buffer_)
        std::free(buffer_ptr_);
}

void sink_buffer::clear()
{
    size_ = 0u;
}

bool sink_buffer::empty() const
{
    return 0u == size_;
}

bool sink_buffer::full() const
{
    return size_ == capacity_;
}

sink_buffer::size_type sink_buffer::size() const
{
    return size_;
}

sink_buffer::size_type sink_buffer::capacity() const
{
    return capacity_;
}

sink_buffer::const_pointer sink_buffer::data() const
{
    return buffer_ptr_;
}

sink_buffer::const_iterator sink_buffer::begin() const
{
    return buffer_ptr_;
}

sink_buffer::const_iterator sink_buffer::end() const
{
    return buffer_ptr_ + size_;
}

void sink_buffer::grow_buffer()
{
    size_type const capacity = capacity_ * 4u;

    if(buffer_ptr_ == static_buffer_)
    {
        void* buffer = std::malloc(capacity);

        if(!buffer)
            throw std::bad_alloc();

        std::memcpy(buffer, static_buffer_, size_);

        buffer_ptr_ = static_cast<char*>(buffer);
    }
    else
    {
        void* buffer = std::realloc(buffer_ptr_, capacity);

        if(!buffer)
            throw std::bad_alloc();

        buffer_ptr_ = static_cast<char*>(buffer);

        capacity_
    }

    capacity_ = capacity;
}

}   // namespace detail
}   // namespace format
}   // namespace missio
