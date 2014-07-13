//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_convert_hpp
#define _missio_json_detail_convert_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

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

template <typename Variant, typename T>
class convert_visitor : public boost::static_visitor<void>
{
public:
    convert_visitor(Variant& variant) :
        variant_(variant)
    {
    }

    convert_visitor(convert_visitor const&) = delete;
    convert_visitor& operator=(convert_visitor const&) = delete;

    void operator()(T) const
    {
    }

    template <typename U>
    void operator()(U const& value) const
    {
        convert(variant_, value, boost::is_convertible<U, T>());
    }

private:
    template <typename U>
    static void convert(Variant& variant, U const& value, boost::mpl::true_)
    {
        variant = static_cast<T>(value);
    }

    template <typename U>
    static void convert(Variant& variant, U, boost::mpl::false_)
    {
        variant = T();
    }

private:
    Variant& variant_;
};

template <typename T>
struct convert
{
    template <typename Variant>
    static void call(Variant& variant)
    {
        boost::apply_visitor(convert_visitor<Variant, T>(variant), variant);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_convert_hpp
