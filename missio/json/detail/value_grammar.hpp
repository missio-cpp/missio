//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_value_grammar_hpp
#define _missio_json_detail_value_grammar_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/value.hpp>
#include <missio/json/detail/string_parser.hpp>

// BOOST headers
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>


namespace missio
{
namespace json
{
namespace detail
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct value_grammar : qi::grammar<Iterator, value(), qi::space_type>
{
    value_grammar() : value_grammar::base_type(start_)
    {
        using qi::_val;
        using qi::lit;
        using qi::bool_;

        typedef qi::strict_real_policies<real> real_policies;
        qi::real_parser<real, real_policies> real_parser;

        qi::int_parser<integer> int_parser;

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

    qi::rule<Iterator, null()> null_;
    qi::rule<Iterator, real()> real_;
    qi::rule<Iterator, string()> string_;
    qi::rule<Iterator, integer()> integer_;
    qi::rule<Iterator, boolean()> boolean_;
    qi::rule<Iterator, array(), qi::space_type> array_;
    qi::rule<Iterator, pair(), qi::space_type> pair_;
    qi::rule<Iterator, object(), qi::space_type> object_;
    qi::rule<Iterator, value(), qi::space_type> value_;
    qi::rule<Iterator, value(), qi::space_type> start_;
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_value_grammar_hpp
