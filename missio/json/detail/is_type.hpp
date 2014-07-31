//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_is_visitor_hpp
#define _missio_json_detail_is_visitor_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

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
class is_visitor : public boost::static_visitor<bool>
{
public:
    is_visitor() = default;

    bool operator()(T) const
    {
        return true;
    }

    template <typename U>
    bool operator()(U) const
    {
        return std::is_convertible<U, T>();
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

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_is_visitor_hpp
