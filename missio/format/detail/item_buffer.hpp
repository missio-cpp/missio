//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_item_buffer_hpp
#define _missio_format_detail_item_buffer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/format_item.hpp>

// STL headers
#include <cstddef>


namespace missio
{
namespace format
{
namespace detail
{

class item_buffer
{
public:
    typedef format_item value_type;
    typedef std::size_t size_type;
    typedef format_item const* iterator;
    typedef format_item const* const_iterator;
    typedef format_item const& reference;
    typedef format_item const& const_reference;

public:
    item_buffer();

    item_buffer(item_buffer const&) = delete;
    item_buffer& operator=(item_buffer const&) = delete;

    bool empty() const;

    size_type size() const;
    size_type capacity() const;

    const_iterator begin() const;
    const_iterator end() const;

    void push_back(format_item const& item);

    const_reference operator[](size_type index) const;

private:
    size_type size_;
    format_item items_[32];
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_item_buffer_hpp
