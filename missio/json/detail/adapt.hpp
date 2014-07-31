//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_adapt_hpp
#define _missio_json_detail_adapt_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/json/types.hpp>
#include <missio/json/string.hpp>
#include <missio/json/binary.hpp>

// STL headers
#include <type_traits>
#include <utility>
#include <string>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T, typename Enable = void>
struct adapt
{
    typedef void type;
};

template <typename T>
struct adapt<T const> : adapt<T>
{
};

template <typename T>
struct adapt<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
    typedef integer type;

    static integer to(T value)
    {
        return static_cast<integer>(value);
    }
};

template <typename T>
struct adapt<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    typedef real type;

    static real to(T value)
    {
        return static_cast<real>(value);
    }
};

template <typename T>
struct adapt<T, typename std::enable_if<std::is_enum<T>::value>::type>
{
    typedef integer type;

    static integer to(T value)
    {
        return static_cast<integer>(value);
    }

    static T from(integer value)
    {
        return static_cast<T>(value);
    }
};

template <typename T>
struct adapt<reference<T>>
{
    typedef T const& type;

    static T const& to(reference<T> const& value)
    {
        return static_cast<T const&>(value);
    }
};

template <typename T>
struct adapt<reference<T const>>
{
    typedef T const& type;

    static T const& to(reference<T const> const& value)
    {
        return static_cast<T const&>(value);
    }
};

template <>
struct adapt<binary>
{
    typedef string type;

    static string to(binary const& value)
    {
        return binary::to_base64_string(value);
    }

    static binary from(string const& value)
    {
        return binary::from_base64_string(value);
    }
};

template <typename Char, typename Traits>
struct adapt<std::basic_string<Char, Traits>>
{
    typedef string type;

    static string to(std::basic_string<Char, Traits>&& value)
    {
        return string(std::forward<std::basic_string<Char, Traits>>(value));
    }
};

template <>
struct adapt<char*>
{
    typedef string type;

    static string to(char const* value)
    {
        return string(value);
    }
};

template <>
struct adapt<wchar_t*>
{
    typedef string type;

    static string to(wchar_t const* value)
    {
        return string(value);
    }
};

template <>
struct adapt<char const*> : adapt<char*>
{
};

template <>
struct adapt<wchar_t const*> : adapt<wchar_t*>
{
};

template <std::size_t N>
struct adapt<char[N]> : adapt<char*>
{
};

template <std::size_t N>
struct adapt<wchar_t[N]> : adapt<wchar_t*>
{
};

template <std::size_t N>
struct adapt<char const[N]> : adapt<char*>
{
};

template <std::size_t N>
struct adapt<wchar_t const[N]> : adapt<wchar_t*>
{
};

template <std::size_t N>
struct adapt<char(&)[N]> : adapt<char*>
{
};

template <std::size_t N>
struct adapt<wchar_t(&)[N]> : adapt<wchar_t*>
{
};

template <std::size_t N>
struct adapt<char const(&)[N]> : adapt<char*>
{
};

template <std::size_t N>
struct adapt<wchar_t const(&)[N]> : adapt<wchar_t*>
{
};

template <>
struct adapt<bool>
{
    typedef boolean type;

    static boolean to(bool value)
    {
        return static_cast<boolean>(value);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_adapt_hpp
