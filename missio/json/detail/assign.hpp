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
#include <missio/json/detail/type_traits.hpp>
#include <missio/json/detail/adapt.hpp>

// BOOST headers
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
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

template <typename Variant>
class assign_helper
{
public:
    template <typename T>
    using is_variant_type = typename boost::mpl::contains<typename Variant::types, remove_ref_const<T>>::type;

    template <typename T>
    using enable_if_variant_type = typename std::enable_if<is_variant_type<T>::value>::type;

    template <typename T>
    using enable_if_not_variant_type = typename std::enable_if<!is_variant_type<T>::value>::type;

public:
    assign_helper() = delete;
    ~assign_helper() = delete;

    template <typename T>
    static void call(Variant& variant, T&& value, enable_if_variant_type<T> const* = nullptr)
    {
        variant = std::forward<T>(value);
    }

    template <typename T>
    static void call(Variant& variant, T const& value, enable_if_variant_type<T> const* = nullptr)
    {
        variant = value;
    }

    template <typename T>
    static void call(Variant& variant, T&& value, enable_if_not_variant_type<T> const* = nullptr)
    {
        variant = adapt<remove_ref_const<T>>::to(std::forward<T>(value));
    }

    template <typename T>
    static void call(Variant& variant, T const& value, enable_if_not_variant_type<T> const* = nullptr)
    {
        variant = adapt<T>::to(value);
    }
};

template <typename Variant, typename T>
void assign_to_variant(Variant& variant, T&& value)
{
    assign_helper<Variant>::call(variant, std::forward<T>(value));
}

template <typename Variant, typename T>
void assign_to_variant(Variant& variant, T const& value)
{
    assign_helper<Variant>::call(variant, value);
}

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_assign_hpp
