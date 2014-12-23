//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_is_type_hpp
#define _missio_json_detail_is_type_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

// STL headers
#include <type_traits>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
struct is_visitor : boost::static_visitor<bool>
{
    is_visitor() = default;
    ~is_visitor() = default;

    bool operator()(T) const
    {
        return true;
    }

    template <typename U>
    bool operator()(U) const
    {
        return std::is_convertible<U, T>::value;
    }
};

template <typename T>
struct is_type
{
    template <typename Variant>
    static bool call(Variant const& variant)
    {
        return boost::apply_visitor(is_visitor<T>(), variant);
    }
};

template <typename T>
struct is_type_impl
{
    template <typename Variant>
    static bool call(Variant const& variant)
    {
        return nullptr != boost::get<T>(&variant);
    }
};

template <>
struct is_type<string> : is_type_impl<string>
{
};

template <>
struct is_type<object> : is_type_impl<object>
{
};

template <>
struct is_type<array> : is_type_impl<array>
{
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_is_type_hpp
