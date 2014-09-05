//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_value_grammar_hpp
#define _missio_json_detail_value_grammar_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/value_get.hpp>

// Implementation headers
#include "string_parser.hpp"
#include "value_traits.hpp"

// BOOST headers
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <typename Iterator, typename Skipper = boost::spirit::qi::space_type>
struct value_grammar : boost::spirit::qi::grammar<Iterator, value(), Skipper>
{
    value_grammar() : value_grammar::base_type(start_)
    {
        using namespace boost::spirit::qi;

        typedef strict_real_policies<real> real_policies;
        real_parser<real, real_policies> real_parser;

        int_parser<integer> int_parser;

        null_       =   lit("null")[_val];

        string_     =   string_parser;

        real_       =   real_parser;

        integer_    =   int_parser;

        boolean_    =   bool_;

        array_      =   '[' >> -(value_ % ',') >> ']';

        pair_       =   string_ >> ':' >> value_;

        object_     =   '{'  >> -(pair_ % ',') >> '}' ;

        value_      =   object_ | array_ | boolean_ | string_ | real_ | integer_ | null_;

        start_      =   object_ | array_;
    }

    boost::spirit::qi::rule<Iterator, null()> null_;
    boost::spirit::qi::rule<Iterator, real()> real_;
    boost::spirit::qi::rule<Iterator, string()> string_;
    boost::spirit::qi::rule<Iterator, integer()> integer_;
    boost::spirit::qi::rule<Iterator, boolean()> boolean_;
    boost::spirit::qi::rule<Iterator, array(), Skipper> array_;
    boost::spirit::qi::rule<Iterator, object_value(), Skipper> pair_;
    boost::spirit::qi::rule<Iterator, object(), Skipper> object_;
    boost::spirit::qi::rule<Iterator, value(), Skipper> value_;
    boost::spirit::qi::rule<Iterator, value(), Skipper> start_;
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_value_grammar_hpp
