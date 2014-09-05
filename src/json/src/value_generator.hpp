//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_value_generator_hpp
#define _missio_json_detail_value_generator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/value_get.hpp>

// Implementation headers
#include "string_generator.hpp"
#include "real_policies.hpp"
#include "value_traits.hpp"

// BOOST headers
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/include/std_pair.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <typename Iterator>
struct value_generator : boost::spirit::karma::grammar<Iterator, value()>
{
    value_generator() : value_generator::base_type(value_)
    {
        using namespace boost::spirit::karma;

        typedef high_precision_real_policies<real> real_policies;
        real_generator<real, real_policies> real_generator;

        int_generator<integer> int_generator;

        null_       =   lit("null")[_1];

        string_     =   string_generator;

        real_       =   real_generator;

        integer_    =   int_generator;

        boolean_    =   bool_;

        array_      =   '[' << -(value_ % ',') << ']';

        pair_       =   string_ << ':' <<  value_;

        object_     =   '{' << -(pair_ % ',') << '}';

        value_      =   object_ | array_ | boolean_ | string_ | real_ | integer_ | null_;
    }

    boost::spirit::karma::rule<Iterator, null()> null_;
    boost::spirit::karma::rule<Iterator, real()> real_;
    boost::spirit::karma::rule<Iterator, string()> string_;
    boost::spirit::karma::rule<Iterator, integer()> integer_;
    boost::spirit::karma::rule<Iterator, boolean()> boolean_;
    boost::spirit::karma::rule<Iterator, array()> array_;
    boost::spirit::karma::rule<Iterator, object_value()> pair_;
    boost::spirit::karma::rule<Iterator, object()> object_;
    boost::spirit::karma::rule<Iterator, value()> value_;
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_value_generator_hpp
