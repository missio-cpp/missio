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

template <typename U, std::size_t N>
struct is_container<std::array<U, N>> : std::true_type
{
};

template <typename U, typename Allocator>
struct is_container<std::list<U, Allocator>> : std::true_type
{
};

template <typename U, typename Allocator>
struct is_container<std::deque<U, Allocator>> : std::true_type
{
};

template <typename U, typename Allocator>
struct is_container<std::vector<U, Allocator>> : std::true_type
{
};

template <typename T>
using is_octet_type = std::integral_constant<bool, sizeof(T) == sizeof(char)>;

template <typename T>
using enable_if_octet_type = typename std::enable_if<is_octet_type<T>::value>::type;

template <typename T>
using enable_if_octet_container = typename std::enable_if<is_container<T>::value && is_octet_type<typename T::value_type>::value>::type;

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_container_traits_hpp
