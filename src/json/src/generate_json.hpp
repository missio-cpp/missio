//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_generate_json_hpp
#define _missio_json_detail_generate_json_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Implementation headers
#include "pretty_value_generator.hpp"
#include "value_generator.hpp"


namespace missio
{
namespace json
{
namespace detail
{

template <typename OutputIterator>
bool generate_json(value const& value, std::size_t indent, OutputIterator out)
{
    static pretty_value_generator<OutputIterator> const generator;
    return boost::spirit::karma::generate(out, generator(indent), value);
}

template <typename OutputIterator>
bool generate_json(value const& value, OutputIterator out)
{
    static value_generator<OutputIterator> const generator;
    return boost::spirit::karma::generate(out, generator, value);
}

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_generate_json_hpp
