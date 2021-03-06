//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_impl_parse_utf8_hpp
#define _missio_unicode_impl_parse_utf8_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <cstdint>


namespace missio
{
namespace unicode
{
namespace impl
{

// Parse UTF-8 byte sequences according to RFC 3629 (http://www.ietf.org/rfc/rfc3629.txt)

struct utf8_octet_sequence
{
    std::uint8_t min;
    std::uint8_t max;

    struct
    {
        std::uint8_t min;
        std::uint8_t max;
    } next[3];
};

utf8_octet_sequence const utf8_octet_sequences[] =
{
    // two octets sequences
    { 0xC2, 0xDF, { { 0x80, 0xBF } } },

    // three octets sequences
    { 0xE0, 0xE0, { { 0xA0, 0xBF }, { 0x80, 0xBF } } },
    { 0xE1, 0xEC, { { 0x80, 0xBF }, { 0x80, 0xBF } } },
    { 0xED, 0xED, { { 0x80, 0x9F }, { 0x80, 0xBF } } },
    { 0xEE, 0xEF, { { 0x80, 0xBF }, { 0x80, 0xBD } } },

    // four octets sequences
    { 0xF0, 0xF0, { { 0x90, 0xBF }, { 0x80, 0xBF }, { 0x80, 0xBF } } },
    { 0xF1, 0xF3, { { 0x80, 0xBF }, { 0x80, 0xBF }, { 0x80, 0xBF } } },
    { 0xF4, 0xF4, { { 0x80, 0x8F }, { 0x80, 0xBF }, { 0x80, 0xBF } } }
};

template <typename OctetIterator>
bool parse_utf8(OctetIterator& pos, OctetIterator end, std::uint32_t& cp)
{
    OctetIterator it(pos);

    if(it == end)
        return false;

    cp = static_cast<std::uint8_t>(*it++);

    if(cp < 0x80)
    {
        pos = it;
        return true;
    }

    for(auto const& first : utf8_octet_sequences)
    {
        if(first.min <= cp && cp <= first.max)
        {
            std::uint32_t bits = 6;

            for(auto const& next : first.next)
            {
                if(!next.max)
                    break;

                if(it == end)
                    return false;

                auto const octet = static_cast<std::uint8_t>(*it++);

                if(octet < next.min || next.max < octet)
                    return false;

                cp = (cp << 6) + (octet & 0x3F);

                bits += 5;
            }

            cp &= (1 << bits) - 1;

            pos = it;
            return true;
        }
    }

    return false;
}

template <typename OctetIterator>
bool skip_utf8(OctetIterator& pos, OctetIterator end)
{
    OctetIterator it(pos);

    if(it == end)
        return false;

    auto octet = static_cast<std::uint8_t>(*it++);

    if(octet < 0x80)
    {
        pos = it;
        return true;
    }

    for(auto const& first : utf8_octet_sequences)
    {
        if(first.min <= octet && octet <= first.max)
        {
            for(auto const& next : first.next)
            {
                if(!next.max)
                    break;

                if(it == end)
                    return false;

                octet = static_cast<std::uint8_t>(*it++);

                if(octet < next.min || next.max < octet)
                    return false;
            }

            pos = it;
            return true;
        }
    }

    return false;
}

}   // namespace impl
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_impl_parse_utf8_hpp
