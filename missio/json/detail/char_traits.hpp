//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_char_traits_hpp
#define _missio_json_detail_char_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <type_traits>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
struct is_char_type : std::false_type
{
};

template <>
struct is_char_type<char> : std::true_type
{
};

template <>
struct is_char_type<signed char> : std::true_type
{
};

template <>
struct is_char_type<unsigned char> : std::true_type
{
};

template <typename T>
using enable_if_char_type = typename std::enable_if<is_char_type<T>::value>::type;

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_char_traits_hpp
