//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_traits_hpp
#define _missio_format_detail_format_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/format_adapter.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Format>
struct format_traits
{
    typedef detail::format_adapter<Format> adapter_type;
};

template <typename Format>
struct format_traits<Format const> : format_traits<Format>
{
};

template <typename Format>
struct format_traits<detail::format_adapter<Format>>
{
    typedef detail::format_adapter<Format> const& adapter_type;
};

template <>
struct format_traits<char const*>
{
    typedef detail::format_adapter<char const*> adapter_type;
};

template <>
struct format_traits<char*> : format_traits<char const*>
{
};

template <std::size_t N>
struct format_traits<char[N]> : format_traits<char const*>
{
};

template <std::size_t N>
struct format_traits<char const[N]> : format_traits<char const*>
{
};

template <std::size_t N>
struct format_traits<char(&)[N]> : format_traits<char const*>
{
};

template <std::size_t N>
struct format_traits<char const(&)[N]> : format_traits<char const*>
{
};

template <typename Format>
using format_adapter_type = typename format_traits<Format>::adapter_type;

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_traits_hpp
