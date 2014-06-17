//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_parse_format_hpp
#define _missio_format_detail_parse_format_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/format_grammar.hpp>
#include <missio/format/detail/item_buffer.hpp>
#include <missio/format/exception.hpp>

// STL headers
#include <string>
#include <cstddef>


namespace missio
{
namespace format
{
namespace detail
{

inline void parse_format(char const* format, std::size_t size, item_buffer& items)
{
    char const* first = format;
    char const* last = first + size;

    static format_grammar<char const*> const grammar;

    if(!qi::parse(first, last, grammar, items) || first != last)
        throw exception("invalid format near: " + std::string(first, last));
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_parse_format_hpp
