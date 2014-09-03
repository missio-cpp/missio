//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_as_visitor_hpp
#define _missio_json_detail_as_visitor_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/exception.hpp>
#include <missio/json/detail/adapt.hpp>

// BOOST headers
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

// STL headers
#include <type_traits>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
class as_visitor : public boost::static_visitor<T>
{
public:
    template <typename U>
    using is_convertible = typename std::is_convertible<U, T>::type;

    template <typename U>
    using is_adapted = typename std::is_same<U, typename adapt<T>::type>::type;

    template <typename U>
    using enable_if_convertible = typename std::enable_if<is_convertible<U>::value && !is_adapted<U>::value>::type;

    template <typename U>
    using enable_if_adapted = typename std::enable_if<!is_convertible<U>::value && is_adapted<U>::value>::type;

    template <typename U>
    using enable_if_invalid = typename std::enable_if<!is_convertible<U>::value && !is_adapted<U>::value>::type;

public:
    as_visitor() = default;
    ~as_visitor() = default;

    T const& operator()(T const& value) const
    {
        return value;
    }

    template <typename U>
    T operator()(U const& value, enable_if_convertible<U> const* = nullptr) const
    {
        return static_cast<T>(value);
    }

    template <typename U>
    T operator()(U const& value, enable_if_adapted<U> const* = nullptr) const
    {
        return adapt<T>::from(value);
    }

    template <typename U>
    T operator()(U const& value, enable_if_invalid<U> const* = nullptr) const
    {
        throw exception("invalid value type");
    }
};

template <typename T>
struct as_type
{
    template <typename Variant>
    static T call(Variant const& variant)
    {
        return boost::apply_visitor(as_visitor<T>(), variant);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_as_visitor_hpp
