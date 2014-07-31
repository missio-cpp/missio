//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_null_traits_hpp
#define _missio_json_detail_null_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/null.hpp>

// BOOST headers
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>


namespace boost
{

template <>
struct is_pod<missio::json::null> : boost::mpl::true_
{
};

template <>
struct is_empty<missio::json::null> : boost::mpl::true_
{
};

template <>
struct is_stateless<missio::json::null> : boost::mpl::true_
{
};

}   // namespace boost

#endif  // _missio_json_detail_null_traits_hpp
