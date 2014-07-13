//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
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
#include <boost/type_traits/conversion_traits.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>


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
    T operator()(U const& value) const
    {
        return as(value, boost::is_convertible<U, T>(), boost::is_same<U, adapted_type>());
    }

private:
    template <typename U, bool adapted>
    static T as(U const& value, boost::mpl::true_, boost::mpl::bool_<adapted>)
    {
        return static_cast<T>(value);
    }

    template <typename U>
    static T as(U const& value, boost::mpl::false_, boost::mpl::true_)
    {
        return adapt<T>::from(value);
    }

    template <typename U>
    static T as(U, boost::mpl::false_, boost::mpl::false_)
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
