//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_grammar_hpp
#define _missio_format_detail_format_grammar_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/format/detail/item_buffer_traits.hpp>

// BOOST headers
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

// STL headers
#include <algorithm>
#include <cstdint>


using missio::format::detail::format_item;

BOOST_FUSION_ADAPT_STRUCT
(
    format_item,
    (std::uint32_t, index)
    (boost::string_ref, string)
)

namespace boost
{
namespace spirit
{
namespace traits
{

template <typename Char, typename Traits, typename Iterator>
struct assign_to_attribute_from_iterators<boost::basic_string_ref<Char, Traits>, Iterator>
{
    static void call(Iterator const& first, Iterator const& last, boost::basic_string_ref<Char, Traits>& attr)
    {
        attr = boost::basic_string_ref<Char, Traits>(&*first, std::distance(first, last));
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

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct format_grammar : qi::grammar<Iterator, item_buffer()>
{
    format_grammar() : format_grammar::base_type(start_)
    {
        using qi::uint_;
        using qi::char_;
        using qi::lit;
        using qi::raw;
        using qi::attr;

        string_     =   raw
                        [
                           *(  ~char_("{}")
                            |   lit("{{")
                            |   lit("}}")
                            )
                        ]
                    ;

        index_      =   '{'
                    >>  uint_
                    >>  '}'
                    ;

        prefix_     =   attr(~0u)
                    >>  string_
                    ;

        item_       =   index_
                    >>  string_
                    ;

        start_      =   prefix_
                    >> *item_
                    ;
    }

    qi::rule<Iterator, boost::string_ref()> string_;
    qi::rule<Iterator, std::uint32_t()> index_;
    qi::rule<Iterator, format_item()> prefix_;
    qi::rule<Iterator, format_item()> item_;
    qi::rule<Iterator, item_buffer()> start_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_grammar_hpp
