//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_base64_hpp
#define _missio_json_detail_base64_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/exception.hpp>

// STL headers
#include <cstdint>
#include <vector>
#include <string>


namespace missio
{
namespace json
{
namespace detail
{

class base64
{
public:
    base64() = delete;

    template <typename InputIterator, typename OutputIterator>
    static void encode(InputIterator first, InputIterator last, OutputIterator dest);

    template <typename InputIterator, typename OutputIterator>
    static void decode(InputIterator first, InputIterator last, OutputIterator dest);

    static std::string encode(std::vector<std::uint8_t> const& value);
    static std::vector<std::uint8_t> decode(std::string const& value);

private:
    static char from_6_bit(std::uint8_t ch);
    static std::uint8_t to_6_bit(std::uint8_t ch);
};

template <typename InputIterator, typename OutputIterator>
void base64::encode(InputIterator first, InputIterator last, OutputIterator dest)
{
    std::size_t count;
    std::uint8_t bytes[3];

    while(first != last)
    {
        for(count = 0; first != last && count < 3; ++first, ++count)
            bytes[count] = static_cast<std::uint8_t>(*first);

        switch(count)
        {
            case 1:
                *dest++ = from_6_bit(bytes[0] >> 2 & 0x3F);
                *dest++ = from_6_bit(bytes[0] << 4 & 0x30);
                *dest++ = '=';
                *dest++ = '=';
                break;

            case 2:
                *dest++ = from_6_bit(bytes[0] >> 2 & 0x3F);
                *dest++ = from_6_bit((bytes[0] << 4 & 0x30) | (bytes[1] >> 4 & 0x0F));
                *dest++ = from_6_bit(bytes[1] << 2 & 0x3C);
                *dest++ = '=';
                break;

            case 3:
                *dest++ = from_6_bit(bytes[0] >> 2 & 0x3F);
                *dest++ = from_6_bit((bytes[0] << 4 & 0x30) | (bytes[1] >> 4 & 0x0F));
                *dest++ = from_6_bit((bytes[1] << 2 & 0x3C) | (bytes[2] >> 6 & 0x03));
                *dest++ = from_6_bit(bytes[2] & 0x3F);
                break;
        }
    }
}

template <typename InputIterator, typename OutputIterator>
void base64::decode(InputIterator first, InputIterator last, OutputIterator dest)
{
    std::size_t count;
    std::uint8_t bytes[4];

    while(first != last)
    {
        for(count = 0; first != last && count < 4; ++first, ++count)
            bytes[count] = static_cast<std::uint8_t>(*first);

        if(4 != count)
            throw exception("invalid BASE-64 data");

        *dest++ = (to_6_bit(bytes[0]) << 2 & 0xFC) | (to_6_bit(bytes[1]) >> 4 & 0x03);

        if('=' != bytes[2])
            *dest++ = (to_6_bit(bytes[1]) << 4 & 0xF0) | (to_6_bit(bytes[2]) >> 2 & 0x0F);

        if('=' != bytes[3])
            *dest++ = (to_6_bit(bytes[2]) << 6 & 0xC0) | to_6_bit(bytes[3]);
    }
}

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_base64_hpp
