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
#include <missio/json/value.hpp>

// Implementation headers
#include "string_parser.hpp"

// BOOST headers
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <typename Iterator>
struct value_grammar : boost::spirit::qi::grammar<Iterator, value(), boost::spirit::qi::space_type>
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

        array_      =   '['
                    >> -(value_ % ',')
                    >>  ']'
                    ;

        pair_       =   string_
                    >>  ':'
                    >>  value_
                    ;

        object_     =   '{'
                    >> -(pair_ % ',')
                    >>  '}'
                    ;

        value_      =   string_
                    |   array_
                    |   object_
                    |   real_
                    |   integer_
                    |   boolean_
                    |   null_
                    ;

        start_      =   array_
                    |   object_
                    ;
    }

    typedef object::value_type pair;

    boost::spirit::qi::rule<Iterator, null()> null_;
    boost::spirit::qi::rule<Iterator, real()> real_;
    boost::spirit::qi::rule<Iterator, string()> string_;
    boost::spirit::qi::rule<Iterator, integer()> integer_;
    boost::spirit::qi::rule<Iterator, boolean()> boolean_;
    boost::spirit::qi::rule<Iterator, array(), boost::spirit::qi::space_type> array_;
    boost::spirit::qi::rule<Iterator, pair(), boost::spirit::qi::space_type> pair_;
    boost::spirit::qi::rule<Iterator, object(), boost::spirit::qi::space_type> object_;
    boost::spirit::qi::rule<Iterator, value(), boost::spirit::qi::space_type> value_;
    boost::spirit::qi::rule<Iterator, value(), boost::spirit::qi::space_type> start_;
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_value_grammar_hpp
