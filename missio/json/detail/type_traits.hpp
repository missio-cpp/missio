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

// STL headers
#include <type_traits>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
using remove_ref_const = typename std::remove_const<typename std::remove_reference<T>::type>::type;

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_type_traits_hpp
