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

std::uint8_t const continuation_octet_min = 0x80;
std::uint8_t const continuation_octet_max = 0xBF;

std::uint16_t const high_surrogate_min = 0xD800;
std::uint16_t const high_surrogate_max = 0xDBFF;

std::uint16_t const low_surrogate_min = 0xDC00;
std::uint16_t const low_surrogate_max = 0xDFFF;

std::uint32_t const surrogate_shift = 10;
std::uint32_t const surrogate_mask = 0x3FF;
std::uint32_t const surrogate_base = 0x10000;

std::uint32_t const replacement_char = 0xFFFD;
std::uint32_t const code_point_max = 0x10FFFF;

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

template <typename UTF8>
bool is_continuation(UTF8 octet)
{
    return continuation_octet_min <= make_uint8(octet) && make_uint8(octet) <= continuation_octet_max;
}

template <typename UTF16>
bool is_surrogate(UTF16 code_unit)
{
    return high_surrogate_min <= make_uint16(code_unit) && make_uint16(code_unit) <= low_surrogate_max;
}

template <typename UTF16>
bool is_high_surrogate(UTF16 code_unit)
{
    return high_surrogate_min <= make_uint16(code_unit) && make_uint16(code_unit) <= high_surrogate_max;
}

template <typename UTF16>
bool is_low_surrogate(UTF16 code_unit)
{
    return low_surrogate_min <= make_uint16(code_unit) && make_uint16(code_unit) <= low_surrogate_max;
}

template <typename UTF16>
std::uint32_t make_code_point(UTF16 high_surrogate, UTF16 low_surrogate)
{
    std::uint32_t code_point;

    code_point = (make_uint16(high_surrogate) - high_surrogate_min) << surrogate_shift;
    code_point += make_uint16(low_surrogate) - low_surrogate_min + surrogate_base;

    return code_point;
}

template <typename UTF32>
bool is_code_point_valid(UTF32 code_point)
{
    return code_point <= code_point_max && code_point != 0xFFFE && code_point != 0xFFFF && !is_surrogate(code_point);
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_common_hpp
