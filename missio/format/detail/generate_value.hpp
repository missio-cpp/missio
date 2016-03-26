//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_generate_value_hpp
#define _missio_format_detail_generate_value_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_iterator.hpp>

// BOOST headers
#include <missio/common/boost_spirit_karma.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink, typename Value, typename Generator>
void generate_value(Sink& sink, Value const& value, Generator const& generator)
{
    boost::spirit::karma::generate(sink_iterator<Sink>(sink), generator, value);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_generate_value_hpp
