//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_convert_hpp
#define _missio_json_detail_convert_hpp

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

template <typename Variant, typename T>
class convert_visitor : public boost::static_visitor<>
{
public:
    template <typename U>
    using is_convertible = typename std::is_convertible<U, T>::type;

    template <typename U>
    using enable_if_convertible = typename std::enable_if<is_convertible<U>::value>::type;

    template <typename U>
    using enable_if_not_convertible = typename std::enable_if<!is_convertible<U>::value>::type;

public:
    explicit convert_visitor(Variant& variant) :
        variant_(variant)
    {
    }

    convert_visitor(convert_visitor const&) = default;
    convert_visitor& operator=(convert_visitor const&) = delete;

    convert_visitor(convert_visitor&&) = default;
    convert_visitor& operator=(convert_visitor&&) = delete;

    void operator()(T) const
    {
    }

    template <typename U>
    void operator()(U const& value, enable_if_convertible<U> const* = nullptr) const
    {
        variant_ = static_cast<T>(value);
    }

    template <typename U>
    void operator()(U, enable_if_not_convertible<U> const* = nullptr) const
    {
        variant_ = T();
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
