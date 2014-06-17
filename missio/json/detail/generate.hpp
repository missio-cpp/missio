//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_generate_hpp
#define _missio_json_detail_generate_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/value_generator.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <typename OutputIterator>
bool generate(value const& value, OutputIterator out)
{
    static value_generator<OutputIterator> const generator;
    return karma::generate(out, generator, value);
}

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_generate_hpp
