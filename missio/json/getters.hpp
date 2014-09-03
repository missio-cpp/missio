//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_getters_hpp
#define _missio_json_getters_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/value.hpp>
#include <missio/json/binary.hpp>


namespace missio
{
namespace json
{

inline bool is_null(value const& value)
{
    return value.is<null>();
}

inline bool is_real(value const& value)
{
    return value.is<real>();
}

inline bool is_integer(value const& value)
{
    return value.is<integer>();
}

inline bool is_boolean(value const& value)
{
    return value.is<boolean>();
}

inline bool is_string(value const& value)
{
    return value.is<string>();
}

inline bool is_array(value const& value)
{
    return value.is<array>();
}

inline bool is_object(value const& value)
{
    return value.is<object>();
}

inline real as_real(value const& value)
{
    return value.as<real>();
}

inline integer as_integer(value const& value)
{
    return value.as<integer>();
}

inline bool as_boolean(value const& value)
{
    return value.as<boolean>();
}

inline string as_string(value const& value)
{
    return value.as<string>();
}

inline array as_array(value const& value)
{
    return value.as<array>();
}

inline object as_object(value const& value)
{
    return value.as<object>();
}

inline binary as_binary(value const& value)
{
    return value.as<binary>();
}

inline real const& get_real(value const& value)
{
    return value.get<real>();
}

inline integer const& get_integer(value const& value)
{
    return value.get<integer>();
}

inline bool const& get_boolean(value const& value)
{
    return value.get<boolean>();
}

inline string const& get_string(value const& value)
{
    return value.get<string>();
}

inline array const& get_array(value const& value)
{
    return value.get<array>();
}

inline object const& get_object(value const& value)
{
    return value.get<object>();
}

}   // namespace json
}   // namespace missio

#endif  // _missio_json_getters_hpp
