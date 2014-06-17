//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_item_buffer_hpp
#define _missio_format_detail_item_buffer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/format_item.hpp>

// BOOST headers
#include <boost/noncopyable.hpp>

// STL headers
#include <cstddef>


namespace missio
{
namespace format
{
namespace detail
{

class item_buffer :
    private boost::noncopyable
{
public:
    typedef format_item value_type;
    typedef std::size_t size_type;
    typedef format_item const* iterator;
    typedef format_item const* const_iterator;
    typedef format_item const& reference;
    typedef format_item const& const_reference;

public:
    item_buffer() :
        size_(0)
    {
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
        return 32;
    }

    const_iterator begin() const
    {
        return items_;
    }

    const_iterator end() const
    {
        return items_ + size_;
    }

    void push_back(format_item const& item)
    {
        if(size_ < 32)
            items_[size_++] = item;
    }

    const_reference operator[](size_type index) const
    {
        return items_[index];
    }

private:
    size_type size_;
    format_item items_[32];
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_item_buffer_hpp
