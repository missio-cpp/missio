//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_assign_hpp
#define _missio_json_detail_assign_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/json/detail/adapt.hpp>

// BOOST headers
#include <boost/mpl/contains.hpp>

// STL headers
#include <type_traits>
#include <utility>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
struct assign
{
    template <typename Variant>
    static void call(Variant& variant, T const& value)
    {
        call(variant, value, boost::mpl::contains<typename Variant::types, T>());
    }

    template <typename Variant>
    static void call(Variant& variant, T const& value, boost::mpl::true_)
    {
        variant = value;
    }

    template <typename Variant>
    static void call(Variant& variant, T const& value, boost::mpl::false_)
    {
        variant = adapt<T>::to(value);
    }
};

template <typename Variant>
void assign_value_to_variant(Variant& variant, value const& value)
{
   variant = value.variant();
}

template <typename T, typename Variant>
void assign_value_to_variant(Variant& variant, T const& value)
{
    assign<typename std::remove_reference<T>::type>::call(variant, value);
}

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_assign_hpp
