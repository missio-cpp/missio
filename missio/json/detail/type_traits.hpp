//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_type_traits_hpp
#define _missio_json_detail_type_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/types.hpp>

// STL headers
#include <type_traits>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
using is_array = typename std::is_same<typename std::decay<T>::type, array>::type;

template <typename T>
using is_object = typename std::is_same<typename std::decay<T>::type, object>::type;

template <typename T>
using is_string = typename std::is_same<typename std::decay<T>::type, string>::type;

template <typename T>
using is_supported_type = std::integral_constant<bool, std::is_arithmetic<T>::value || std::is_class<T>::value || std::is_enum<T>::value>;

template <typename T>
using is_composite_type = std::integral_constant<bool, is_array<T>::value || is_object<T>::value || is_string<T>::value>;

template <typename T>
using is_scalar_type = std::integral_constant<bool, !is_composite_type<T>::value && is_supported_type<T>::value>;

template <typename T>
using enable_if_supported_type = typename std::enable_if<is_supported_type<T>::value>::type;

template <typename T>
using enable_if_composite_type = typename std::enable_if<is_composite_type<T>::value>::type;

template <typename T>
using enable_if_scalar_type = typename std::enable_if<is_scalar_type<T>::value>::type;

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_type_traits_hpp
