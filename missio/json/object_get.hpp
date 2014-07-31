//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_object_get_hpp
#define _missio_json_object_get_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/value.hpp>

// BOOST headers
#include <boost/optional.hpp>


namespace missio
{
namespace json
{

template <typename T>
inline T object_get(value const& value, string const& key, T const& default_value = T())
{
    return value.get<object>().contains(key) ? value[key].as<T>() : default_value;
}

template <typename T>
inline boost::optional<T> object_try_get(value const& value, string const& key)
{
    return value.get<object>().contains(key) ? value[key].as<T>() : boost::optional<T>();
}

}   // namespace json
}   // namespace missio

#endif  // _missio_json_object_get_hpp
