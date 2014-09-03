//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_parse_json_hpp
#define _missio_json_detail_parse_json_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Implementation headers
#include "value_grammar.hpp"


namespace missio
{
namespace json
{
namespace detail
{

template <typename Iterator>
bool parse_json(Iterator first, Iterator last, value& value)
{
    static value_grammar<Iterator> const grammar;

    return boost::spirit::qi::phrase_parse(first, last, grammar, boost::spirit::qi::space, value) && first == last;
}

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_parse_json_hpp
