//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_string_parser_hpp
#define _missio_json_detail_string_parser_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/extract_string.hpp>

// BOOST headers
#include <boost/spirit/include/qi.hpp>


namespace missio
{
namespace json
{
namespace detail
{

BOOST_SPIRIT_TERMINAL(string_parser)

}   // namespace detail
}   // namespace json
}   // namespace missio

namespace boost
{
namespace spirit
{

template <>
struct use_terminal<qi::domain, missio::json::detail::tag::string_parser> : mpl::true_
{
};

}   // namespace spirit
}   // namespace boost

namespace missio
{
namespace json
{
namespace detail
{

struct any_string_parser : boost::spirit::qi::primitive_parser<any_string_parser>
{
    template <typename Context, typename Iterator>
    struct attribute
    {
        typedef string type;
    };

    template <typename Iterator, typename Context, typename Skipper, typename Attribute>
    static bool parse(Iterator& first, Iterator const& last, Context&, Skipper const& skipper, Attribute& attr)
    {
        boost::spirit::qi::skip_over(first, last, skipper);
        return extract_string::call(first, last, attr);
    }

    template <typename Context>
    static boost::spirit::info what(Context const&)
    {
        return boost::spirit::info("json-string-parser");
    }

private:
    // prevent MSVC warning C4512: assignment operator could not be generated
    any_string_parser& operator=(any_string_parser const& other);
};

}   // namespace detail
}   // namespace json
}   // namespace missio

namespace boost
{
namespace spirit
{
namespace qi
{

template <typename Modifiers>
struct make_primitive<missio::json::detail::tag::string_parser, Modifiers>
{
    typedef missio::json::detail::any_string_parser result_type;

    result_type operator()(unused_type, unused_type) const
    {
        return result_type();
    }
};

}   // namespace qi
}   // namespace spirit
}   // namespace boost

#endif  // _missio_json_detail_string_parser_hpp
