//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_types_hpp
#define _missio_json_types_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)


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

template <typename T>
class reference;

}   // namespace json
}   // namespace missio

#endif  // _missio_json_types_hpp
