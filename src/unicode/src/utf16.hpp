//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_utf16_hpp
#define _missio_unicode_impl_utf16_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/unicode/exception.hpp>

// Implementation headers
#include "common.hpp"

// STL headers
#include <iterator>
#include <cstdint>


namespace missio
{
namespace unicode
{
namespace impl
{
namespace utf16
{

std::uint16_t const high_surrogate_min = 0xD800;
std::uint16_t const high_surrogate_max = 0xDBFF;

std::uint16_t const low_surrogate_min = 0xDC00;
std::uint16_t const low_surrogate_max = 0xDFFF;

std::uint32_t const surrogate_shift = 10;
std::uint32_t const surrogate_mask = 0x3FF;
std::uint32_t const surrogate_base = 0x10000;

template <typename UTF16>
bool is_surrogate(UTF16 code_unit)
{
    return high_surrogate_min <= static_cast<std::uint16_t>(code_unit) &&
           low_surrogate_max >= static_cast<std::uint16_t>(code_unit);
}

template <typename UTF16>
bool is_high_surrogate(UTF16 code_unit)
{
    return high_surrogate_min <= static_cast<std::uint16_t>(code_unit) &&
           high_surrogate_max >= static_cast<std::uint16_t>(code_unit);
}

template <typename UTF16>
bool is_low_surrogate(UTF16 code_unit)
{
    return low_surrogate_min <= static_cast<std::uint16_t>(code_unit) &&
           low_surrogate_max >= static_cast<std::uint16_t>(code_unit);
}

template <typename UTF16>
std::uint32_t make_code_point(UTF16 high_surrogate, UTF16 low_surrogate)
{
    std::uint32_t code_point;

    code_point = (static_cast<std::uint16_t>(high_surrogate) - high_surrogate_min) << surrogate_shift;
    code_point += static_cast<std::uint16_t>(low_surrogate) - low_surrogate_min + surrogate_base;

    return code_point;
}

template <typename UTF16Iterator>
std::uint32_t next(UTF16Iterator& pos, UTF16Iterator end)
{
    UTF16Iterator it(pos);

    if(pos == end)
        throw input_underflow_error();

    std::uint16_t const cp1 = static_cast<std::uint16_t>(*it++);

    if(is_low_surrogate(cp1))
        throw invalid_utf16_code_unit(cp1);

    if(is_high_surrogate(cp1))
    {
        if(it == end)
            throw invalid_utf16_code_unit(cp1);

        std::uint16_t const cp2 = static_cast<std::uint16_t>(*it++);

        if(!is_low_surrogate(cp2))
            throw invalid_utf16_code_unit(cp2);

        return make_code_point(cp1, cp2);
    }

    pos = it;
    return cp1;
}

template <typename UTF16Iterator>
std::uint32_t peek_next(UTF16Iterator pos, UTF16Iterator end)
{
    return next(pos, end);
}

template <typename OutputIterator>
void write(std::uint32_t cp, OutputIterator dest)
{
    if(is_surrogate(cp))
        throw invalid_utf32_code_point(cp);

    if(!is_code_point_valid(cp))
        throw invalid_utf32_code_point(cp);

    if(cp < surrogate_base)
    {
        *dest++ = static_cast<std::uint16_t>(cp);
    }
    else
    {
        cp -= surrogate_base;

        std::uint32_t const high_surrogate = cp >> surrogate_shift;
        std::uint32_t const low_surrogate = cp & surrogate_mask;

        *dest++ = static_cast<std::uint16_t>(high_surrogate + high_surrogate_min);
        *dest++ = static_cast<std::uint16_t>(low_surrogate + low_surrogate_min);
    }
}

}   // namespace utf16
}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_utf16_hpp
