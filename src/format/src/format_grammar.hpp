//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_grammar_hpp
#define _missio_format_detail_format_grammar_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/format/detail/string_view.hpp>

// BOOST headers
#include <missio/common/boost_spirit_qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

// Implementation headers
#include "item_buffer_traits.hpp"

// STL headers
#include <iterator>
#include <cstdint>


using missio::format::detail::format_item;
using missio::format::detail::string_view;

BOOST_FUSION_ADAPT_STRUCT
(
    format_item,
    (std::uint32_t, index)
    (string_view, string)
)

namespace boost
{
namespace spirit
{
namespace traits
{

template <typename Iterator>
struct assign_to_attribute_from_iterators<missio::format::detail::string_view, Iterator>
{
    static void call(Iterator const& first, Iterator const& last, missio::format::detail::string_view& attr)
    {
        attr = missio::format::detail::string_view(&*first, std::distance(first, last));
    }
};

}   // namespace traits
}   // namespace spirit
}   // namespace boost

namespace missio
{
namespace format
{
namespace detail
{

template <typename Iterator>
struct format_grammar : boost::spirit::qi::grammar<Iterator, item_buffer()>
{
    format_grammar() : format_grammar::base_type(start_)
    {
        using namespace boost::spirit::qi;

        string_     =   raw[ *( ~char_("{}") | "{{" | "}}" ) ];

        index_      =   '{' >> uint_ >> '}';

        prefix_     =   attr(~0u) >> string_;

        item_       =   index_ >> string_;

        start_      =   prefix_ >> *item_;
    }

    boost::spirit::qi::rule<Iterator, string_view()> string_;
    boost::spirit::qi::rule<Iterator, std::uint32_t()> index_;
    boost::spirit::qi::rule<Iterator, format_item()> prefix_;
    boost::spirit::qi::rule<Iterator, format_item()> item_;
    boost::spirit::qi::rule<Iterator, item_buffer()> start_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_grammar_hpp
