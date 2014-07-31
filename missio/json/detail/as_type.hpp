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
    typedef typename adapt<T>::type adapted_type;

public:
    as_visitor() = default;

    T const& operator()(T const& value) const
    {
        return value;
    }

    template <typename U>
    typename std::enable_if<std::is_convertible<U, T>::value, T>::type operator()(U const& value) const
    {
        return static_cast<T>(value);
    }

    template <typename U>
    typename std::enable_if<std::is_same<U, adapted_type>::value, T>::type operator()(U const& value) const
    {
        return adapt<T>::from(value);
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
