//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_utf8_hpp
#define _missio_unicode_impl_utf8_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/unicode/exception.hpp>

// Implementation headers
#include "parse_utf8.hpp"
#include "common.hpp"
#include "utf16.hpp"

// STL headers
#include <algorithm>
#include <iterator>


namespace missio
{
namespace unicode
{
namespace impl
{
namespace utf8
{

std::uint8_t const continuation_octet_min = 0x80;
std::uint8_t const continuation_octet_max = 0xBF;

std::uint8_t const byte_order_mark[] { 0xEF, 0xBB, 0xBF };

template <typename UTF8>
bool is_continuation_octet(UTF8 octet)
{
    return continuation_octet_min <= make_uint8(octet) && make_uint8(octet) <= continuation_octet_max;
}

template <typename OutputIterator>
void write_byte_order_mark(OutputIterator dest)
{
    std::copy(std::begin(byte_order_mark), std::end(byte_order_mark), dest);
}

template <typename OctetIterator>
bool skip_byte_order_mark(OctetIterator& pos, OctetIterator end)
{
    OctetIterator it(pos);

    for(std::uint8_t const bom_octet : byte_order_mark)
    {
        if(it == end)
            return false;

        std::uint8_t const octet = make_uint8(*it++);

        if(octet != bom_octet)
            return false;
    }

    pos = it;

    return true;
}

template <typename OctetIterator>
bool starts_with_byte_order_mark(OctetIterator pos, OctetIterator end)
{
    return skip_byte_order_mark(pos, end);
}

template <typename OctetIterator>
std::uint32_t next(OctetIterator& pos, OctetIterator end)
{
    std::uint32_t cp;
    OctetIterator it(pos);

    if(pos == end)
        throw input_underflow_error();

    if(!parse_utf8(it, end, cp))
        throw invalid_utf8_sequence(it, end);

    pos = it;

    return cp;
}

template <typename OctetIterator>
std::uint32_t peek_next(OctetIterator pos, OctetIterator end)
{
    return next(pos, end);
}

template <typename OctetIterator>
std::uint32_t previous(OctetIterator& pos, OctetIterator begin)
{
    OctetIterator it(pos);
    OctetIterator end(pos);

    if(begin == end)
        throw input_underflow_error();

    while(is_continuation_octet(*--it))
    {
        if(it == begin)
            throw invalid_utf8_sequence(begin, end);
    }

    std::uint32_t const cp = peek_next(it, end);

    pos = it;

    return cp;
}

template <typename OctetIterator>
std::uint32_t peek_previous(OctetIterator pos, OctetIterator begin)
{
    return previous(pos, begin);
}

template <typename OctetIterator, typename Distance>
OctetIterator advance(OctetIterator& pos, OctetIterator end, Distance n)
{
    while(n-- > 0)
        next(pos, end);

    return pos;
}

template <typename OctetIterator> 
std::size_t length(OctetIterator begin, OctetIterator end)
{
    std::size_t n;

    for(n = 0u; begin != end; ++n)
        next(begin, end);

    return n;
}

template <typename OutputIterator>
void write(std::uint32_t cp, OutputIterator dest)
{
    if(utf16::is_surrogate(cp))
        throw invalid_utf32_code_point(cp);

    if(!is_code_point_valid(cp))
        throw invalid_utf32_code_point(cp);

    if(cp < 0x80)
    {
        *dest++ = static_cast<std::uint8_t>(cp);
    }
    else if(cp < 0x800)
    {
        *dest++ = static_cast<std::uint8_t>(0xC0 | ((cp >> 6) & 0x1F));
        *dest++ = static_cast<std::uint8_t>(0x80 | (cp & 0x3F));
    }
    else if(cp < 0x10000)
    {
        *dest++ = static_cast<std::uint8_t>(0xE0 | ((cp >> 12) & 0x0F));
        *dest++ = static_cast<std::uint8_t>(0x80 | ((cp >> 6) & 0x3F));
        *dest++ = static_cast<std::uint8_t>(0x80 | (cp & 0x3F));
    }
    else if(cp < 0x110000)
    {
        *dest++ = static_cast<std::uint8_t>(0xF0 | ((cp >> 18) & 0x07));
        *dest++ = static_cast<std::uint8_t>(0x80 | ((cp >> 12) & 0x3F));
        *dest++ = static_cast<std::uint8_t>(0x80 | ((cp >> 6) & 0x3F));
        *dest++ = static_cast<std::uint8_t>(0x80 | (cp & 0x3F));
    }
}

template <typename OctetIterator, typename OutputIterator>
void replace_invalid(OctetIterator begin, OctetIterator end, OutputIterator dest, std::uint32_t replacement_char)
{
    while(begin != end)
    {
        std::uint32_t cp;

        if(is_continuation_octet(*begin))
        {
            cp = replacement_char;
            ++begin;
        }
        else
        {
            if(!parse_utf8(begin, end, cp))
            {
                while(++begin != end)
                {
                    if(!is_continuation_octet(*begin))
                        break;
                }

                cp = replacement_char;
            }
        }

        write(cp, dest);
    }
}

template <typename OctetIterator, typename OutputIterator>
void replace_invalid(OctetIterator begin, OctetIterator end, OutputIterator dest)
{
    replace_invalid(begin, end, dest, replacement_char);
}

template <typename OctetIterator>
OctetIterator find_invalid(OctetIterator begin, OctetIterator end)
{
    while(begin != end)
    {
        std::uint32_t cp;
        OctetIterator it(begin);

        if(!parse_utf8(it, end, cp))
            break;

        begin = it;
    }

    return begin;
}

template <typename OctetIterator>
bool is_valid(OctetIterator begin, OctetIterator end)
{
    return find_invalid(begin, end) == end;
}

template <typename OctetIterator>
void validate(OctetIterator begin, OctetIterator end)
{
    while(begin != end)
        next(begin, end);
}

}   // namespace utf8
}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_utf8_hpp
