//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/detail/item_buffer.hpp>


namespace missio
{
namespace format
{
namespace detail
{

item_buffer::item_buffer() :
    size_(0u)
{
}

bool item_buffer::empty() const
{
    return 0u == size_;
}

item_buffer::size_type item_buffer::size() const
{
    return size_;
}

item_buffer::size_type item_buffer::capacity() const
{
    return 32u;
}

item_buffer::const_iterator item_buffer::begin() const
{
    return items_;
}

item_buffer::const_iterator item_buffer::end() const
{
    return items_ + size_;
}

void item_buffer::push_back(format_item const& item)
{
    if(size_ < 32u)
        items_[size_++] = item;
}

item_buffer::const_reference item_buffer::operator[](size_type index) const
{
    return items_[index];
}

}   // namespace detail
}   // namespace format
}   // namespace missio
