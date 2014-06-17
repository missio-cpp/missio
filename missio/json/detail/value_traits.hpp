//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_value_traits_hpp
#define _missio_json_detail_value_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/value_get.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace boost
{
namespace spirit
{
namespace traits
{

template <>
struct not_is_variant<missio::json::value, karma::domain> : mpl::false_
{
};

template <>
struct variant_which<missio::json::value>
{
    static int call(missio::json::value const& value)
    {
        return value.which();
    }
};

}   // namespace traits
}   // namespace spirit
}   // namespace boost

#endif  // _missio_json_detail_value_traits_hpp
