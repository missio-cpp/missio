//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_array_ref_hpp
#define _missio_json_array_ref_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/array.hpp>
#include <missio/json/reference.hpp>


namespace missio
{
namespace json
{

typedef reference<array> array_ref;
typedef reference<array const> array_cref;

}   // namespace json
}   // namespace missio

#endif  // _missio_json_array_ref_hpp
