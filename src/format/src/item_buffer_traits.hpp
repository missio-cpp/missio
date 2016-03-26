//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_item_buffer_traits_hpp
#define _missio_format_detail_item_buffer_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/format/detail/item_buffer.hpp>

// BOOST headers
#include <missio/common/boost_spirit_qi.hpp>


namespace boost
{
namespace spirit
{
namespace traits
{

template <>
struct is_container<missio::format::detail::item_buffer> : mpl::true_
{
};

template <>
struct container_value<missio::format::detail::item_buffer> : mpl::identity<missio::format::detail::format_item>
{
};

template <>
struct push_back_container<missio::format::detail::item_buffer, missio::format::detail::format_item>
{
    static bool call(missio::format::detail::item_buffer& items, missio::format::detail::format_item const& item)
    {
        items.push_back(item);
        return true;
    }
};

}   // namespace traits
}   // namespace spirit
}   // namespace boost

#endif  // _missio_format_detail_item_buffer_traits_hpp
