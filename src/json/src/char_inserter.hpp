//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_char_inserter_hpp
#define _missio_json_detail_char_inserter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <cstdint>


namespace missio
{
namespace json
{
namespace detail
{

class char_inserter
{
public:
    template <typename OutputIterator>
    static bool call(OutputIterator& sink, unsigned char const ch)
    {
        if(ch > 0x1Fu)
        {
            switch(ch)
            {
                case '"':
                case '\\':
                    *sink++ = '\\';   // no break after, intentionally

                default:
                    *sink++ = static_cast<char>(ch);
            }

            return true;
        }

        if(insert_escape(sink, ch))
            return true;

        if(insert_utf16(sink, ch))
            return true;

        return false;
    }

private:
    template <typename OutputIterator>
    static bool insert_escape(OutputIterator& sink, unsigned char const ch)
    {
        char temp;

        switch(ch)
        {
            case '\b': temp = 'b'; break;
            case '\f': temp = 'f'; break;
            case '\n': temp = 'n'; break;
            case '\r': temp = 'r'; break;
            case '\t': temp = 't'; break;

            default:
                return false;
        }

        *sink++ = '\\';
        *sink++ = temp;

        return true;
    }

    template <typename OutputIterator>
    static bool insert_utf16(OutputIterator& sink, std::uint16_t const ch)
    {
        static char const hex_digits[] = "0123456789ABCDEF";

        *sink++ = '\\';
        *sink++ = 'u';
        *sink++ = hex_digits[0x0F & (ch >> 12)];
        *sink++ = hex_digits[0x0F & (ch >> 8)];
        *sink++ = hex_digits[0x0F & (ch >> 4)];
        *sink++ = hex_digits[0x0F & ch];

        return true;
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_char_inserter_hpp
