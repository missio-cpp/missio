//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_utf16_hpp
#define _missio_unicode_utf16_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/unicode/impl/common.hpp>
#include <missio/unicode/exception.hpp>

// STL headers
#include <iterator>
#include <cstdint>


namespace missio
{
namespace unicode
{
namespace utf16
{

template <typename UTF16Iterator>
std::uint32_t next(UTF16Iterator& pos, UTF16Iterator end)
{
    UTF16Iterator it(pos);

    if(pos == end)
        throw input_underflow_error();

    std::uint32_t cp = impl::make_uint16(*it++);

    if(impl::is_low_surrogate(cp))
        throw invalid_utf16_code_unit(cp);

    if(impl::is_high_surrogate(cp))
    {
        if(it == end)
            throw invalid_utf16_code_unit(cp);

        std::uint32_t const low_surrogate = impl::make_uint16(*it++);

        if(!impl::is_low_surrogate(low_surrogate))
            throw invalid_utf16_code_unit(low_surrogate);

        cp = impl::make_code_point(cp, low_surrogate);
    }

    pos = it;

    return cp;
}

template <typename UTF16Iterator>
std::uint32_t peek_next(UTF16Iterator pos, UTF16Iterator end)
{
    return next(pos, end);
}

template <typename OutputIterator>
void write(std::uint32_t cp, OutputIterator dest)
{
    if(!impl::is_code_point_valid(cp))
        throw invalid_utf32_code_point(cp);

    if(cp < impl::surrogate_base)
    {
        *dest++ = static_cast<std::uint16_t>(cp);
    }
    else
    {
        cp -= impl::surrogate_base;

        std::uint32_t const high_surrogate = cp >> impl::surrogate_shift;
        std::uint32_t const low_surrogate = cp & impl::surrogate_mask;

        *dest++ = static_cast<std::uint16_t>(high_surrogate + impl::high_surrogate_min);
        *dest++ = static_cast<std::uint16_t>(low_surrogate + impl::low_surrogate_min);
    }
}

template <typename UTF16Iterator>
bool is_valid(UTF16Iterator begin, UTF16Iterator end)
{
    while(begin != end)
    {
        if(impl::is_low_surrogate(*begin))
            return false;

        if(impl::is_high_surrogate(*begin++))
        {
            if(begin != end)
            {
                if(impl::is_low_surrogate(*begin++))
                    continue;
            }

            return false;
        }
    }

    return true;
}

template <typename UTF16Iterator>
void validate(UTF16Iterator begin, UTF16Iterator end)
{
    while(begin != end)
        next(begin, end);
}

}   // namespace utf16
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_utf16_hpp
