//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_container_traits_hpp
#define _missio_json_detail_container_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/char_traits.hpp>

// STL headers
#include <type_traits>
#include <vector>
#include <deque>
#include <array>
#include <list>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
struct is_container : std::false_type
{
};

template <typename Char, std::size_t N>
struct is_container<std::array<Char, N>> : std::true_type
{
};

template <typename Char, typename Allocator>
struct is_container<std::list<Char, Allocator>> : std::true_type
{
};

template <typename Char, typename Allocator>
struct is_container<std::deque<Char, Allocator>> : std::true_type
{
};

template <typename Char, typename Allocator>
struct is_container<std::vector<Char, Allocator>> : std::true_type
{
};

template <typename T>
using enable_if_char_container = typename std::enable_if<is_container<T>::value && is_char_type<typename T::value_type>::value>::type;

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_container_traits_hpp
