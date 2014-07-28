//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_common_hpp
#define _missio_unicode_impl_common_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <cstdint>


namespace missio
{
namespace unicode
{
namespace impl
{

std::uint32_t const code_point_max = 0x10FFFF;
std::uint32_t const replacement_char = 0xFFFD;

template <typename T>
std::uint8_t make_uint8(T val)
{
    return static_cast<std::uint8_t>(val & 0xFF);
}

template <typename T>
std::uint16_t make_uint16(T val)
{
    return static_cast<std::uint16_t>(val & 0xFFFF);
}

template <typename T>
std::uint32_t make_uint32(T val)
{
    return static_cast<std::uint32_t>(val & 0xFFFFFFFF);
}

template <typename UTF32>
bool is_code_point_valid(UTF32 cp)
{
    return cp <= code_point_max && cp != 0xFFFE && cp != 0xFFFF;
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_common_hpp
