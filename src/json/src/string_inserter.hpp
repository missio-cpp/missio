//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_string_inserter_hpp
#define _missio_json_detail_string_inserter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/string.hpp>

// Implementation headers
#include "char_inserter.hpp"

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace missio
{
namespace json
{
namespace detail
{

struct string_inserter
{
    template <typename OutputIterator>
    static bool call(OutputIterator& sink, char const* str)
    {
        *sink++ = '"';

        for(char ch = *str; 0 != ch; ch = *++str)
            char_inserter::call(sink, ch);

        *sink++ = '"';

        return boost::spirit::karma::detail::sink_is_good(sink);
    }

    template <typename OutputIterator>
    static bool call(OutputIterator& sink, string const& str)
    {
        return call(sink, str.c_str());
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_string_inserter_hpp
