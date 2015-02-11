//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_pretty_value_generator_hpp
#define _missio_json_detail_pretty_value_generator_hpp

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
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/std_pair.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <typename Iterator>
struct pretty_value_generator : boost::spirit::karma::grammar<Iterator, value(std::size_t)>
{
    pretty_value_generator() : pretty_value_generator::base_type(start_)
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

        indent_     =   repeat(_r1)[' '];

        entry_      =   eol << indent_(_r1) <<  value_(_r1, _r2);

        array_      =   '[' << -((entry_(_r1 + _r2, _r2) % ',') << eol << indent_(_r1)) <<  ']';

        pair_       =   eol << indent_(_r1) << string_ << ':' << ' ' << value_(_r1, _r2);

        object_     =   '{' << -((pair_(_r1 + _r2, _r2) % ',') << eol << indent_(_r1)) << '}';

        value_      =   object_(_r1, _r2) | array_(_r1, _r2) | boolean_ | string_ | real_ | integer_ | null_;

        start_      =   value_(0, _r1);
    }

    boost::spirit::karma::rule<Iterator, null()> null_;
    boost::spirit::karma::rule<Iterator, real()> real_;
    boost::spirit::karma::rule<Iterator, string()> string_;
    boost::spirit::karma::rule<Iterator, integer()> integer_;
    boost::spirit::karma::rule<Iterator, boolean()> boolean_;

    boost::spirit::karma::rule<Iterator, void(std::size_t)> indent_;

    boost::spirit::karma::rule<Iterator, value(std::size_t, std::size_t)> entry_;
    boost::spirit::karma::rule<Iterator, array(std::size_t, std::size_t)> array_;
    boost::spirit::karma::rule<Iterator, object_value(std::size_t, std::size_t)> pair_;
    boost::spirit::karma::rule<Iterator, object(std::size_t, std::size_t)> object_;
    boost::spirit::karma::rule<Iterator, value(std::size_t, std::size_t)> value_;

    boost::spirit::karma::rule<Iterator, value(std::size_t)> start_;
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_pretty_value_generator_hpp
