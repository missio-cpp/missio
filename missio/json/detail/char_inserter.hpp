//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_char_inserter_hpp
#define _missio_json_detail_char_inserter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/spirit/include/karma.hpp>


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
        if(0x1F < ch)
        {
            switch(ch)
            {
                case '"':
                case '\\':
                    *sink++ = '\\';

                default:
                    *sink++ = char(ch);
            }
        }
        else
        {
            *sink++ = '\\';

            switch(ch)
            {
                case '\b':
                    *sink++ = 'b';
                    break;

                case '\f':
                    *sink++ = 'f';
                    break;

                case '\n':
                    *sink++ = 'n';
                    break;

                case '\r':
                    *sink++ = 'r';
                    break;

                case '\t':
                    *sink++ = 't';
                    break;

                default:
                    insert_utf16(sink, ch);
            }
        }

        return true;
    }

private:
    template <typename OutputIterator>
    static bool insert_utf16(OutputIterator& sink, unsigned char const ch)
    {
        static char const hex_digits[] = "0123456789ABCDEF";

        *sink++ = 'u';
        *sink++ = '0';
        *sink++ = '0';
        *sink++ = hex_digits[ch >> 4];
        *sink++ = hex_digits[ch & 15];

        return true;
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_char_inserter_hpp
