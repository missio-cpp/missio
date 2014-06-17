//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_buffer_hpp
#define _missio_format_detail_sink_buffer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST header
#include <boost/noncopyable.hpp>

// STL headers
#include <iostream>
#include <cstring>
#include <cstdlib>


namespace missio
{
namespace format
{
namespace detail
{

class sink_buffer :
    private boost::noncopyable
{
public:
    typedef char value_type;
    typedef std::size_t size_type;
    typedef char const* iterator;
    typedef char const* const_iterator;
    typedef char const& reference;
    typedef char const& const_reference;

public:
    sink_buffer() :
        capacity_(sizeof(static_buffer_)),
        buffer_ptr_(static_buffer_),
        size_(0)
    {
    }

    ~sink_buffer()
    {
        if(sizeof(static_buffer_) != capacity_)
            std::free(buffer_ptr_);
    }

    void clear()
    {
        size_ = 0;
    }

    bool empty() const
    {
        return 0 == size_;
    }

    size_type size() const
    {
        return size_;
    }

    size_type capacity() const
    {
        return capacity_;
    }

    char const* data() const
    {
        return buffer_ptr_;
    }

    const_iterator begin() const
    {
        return buffer_ptr_;
    }

    const_iterator end() const
    {
        return buffer_ptr_ + size_;
    }

    void put(char ch)
    {
        buffer_ptr_[size_++] = ch;

        if(size_ == capacity_)
            grow_buffer();
    }

private:
#if defined(__GNUC__)
    __attribute__((noinline)) void grow_buffer()
#elif defined(_MSC_VER)
    __declspec(noinline) void grow_buffer()
#else
    void grow_buffer()
#endif
    {
        size_type const capacity(capacity_ * 4);

        if(sizeof(static_buffer_) == capacity_)
            buffer_ptr_ = reinterpret_cast<char*>(std::malloc(capacity));
        else
            buffer_ptr_ = reinterpret_cast<char*>(std::realloc(buffer_ptr_, capacity));

        if(!buffer_ptr_)
            throw std::bad_alloc();

        if(sizeof(static_buffer_) == capacity_)
            std::memcpy(buffer_ptr_, static_buffer_, size_);

        capacity_ = capacity;
    }

private:
    char static_buffer_[128];
    size_type capacity_;
    char* buffer_ptr_;
    size_type size_;
};

inline std::ostream& operator<<(std::ostream& os, sink_buffer const& buffer)
{
    os.write(buffer.data(), buffer.size());
    return os;
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_buffer_hpp
