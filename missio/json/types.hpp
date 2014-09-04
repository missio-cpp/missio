//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_types_hpp
#define _missio_json_types_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <utility>


namespace missio
{
namespace json
{

class value;
class array;
class object;
class string;

typedef double real;
typedef bool boolean;
typedef long long integer;

typedef std::pair<string, value> object_value;

}   // namespace json
}   // namespace missio

#endif  // _missio_json_types_hpp
