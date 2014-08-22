//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_parse_format_hpp
#define _missio_format_detail_parse_format_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/item_buffer.hpp>
#include <missio/format/exception.hpp>

// Implementation headers
#include "format_grammar.hpp"

// STL headers
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Iterator>
void parse_format(Iterator first, Iterator last, item_buffer& items)
{
    static format_grammar<Iterator> const grammar;

    if(!boost::spirit::qi::parse(first, last, grammar, items) || first != last)
        throw exception("invalid format near: " + std::string(first, last));
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_parse_format_hpp
