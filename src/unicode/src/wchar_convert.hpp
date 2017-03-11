//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_wchar_convert_hpp
#define _missio_unicode_impl_wchar_convert_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Implementation headers
#include "convert.hpp"

// STL headers
#include <algorithm>


namespace missio
{
namespace unicode
{
namespace impl
{

template <std::size_t>
struct wchar_convert_impl;

template <>
struct wchar_convert_impl<sizeof(char16_t)>
{
    template <typename InputIterator, typename OutputIterator>
    static void to_utf8(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf16_to_utf8(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void to_utf16(InputIterator first, InputIterator last, OutputIterator dest)
    {
        std::copy(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void to_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf16_to_utf32(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void from_utf8(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf8_to_utf16(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void from_utf16(InputIterator first, InputIterator last, OutputIterator dest)
    {
        std::copy(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void from_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf32_to_utf16(first, last, dest);
    }
};

template <>
struct wchar_convert_impl<sizeof(char32_t)>
{
    template <typename InputIterator, typename OutputIterator>
    static void to_utf8(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf32_to_utf8(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void to_utf16(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf32_to_utf16(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void to_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        std::copy(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void from_utf8(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf8_to_utf32(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void from_utf16(InputIterator first, InputIterator last, OutputIterator dest)
    {
        utf16_to_utf32(first, last, dest);
    }

    template <typename InputIterator, typename OutputIterator>
    static void from_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        std::copy(first, last, dest);
    }
};

struct wchar_convert : wchar_convert_impl<sizeof(wchar_t)>
{
};

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_wchar_convert_hpp
