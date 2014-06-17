//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_string_generator_hpp
#define _missio_json_detail_string_generator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/string_inserter.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace missio
{
namespace json
{
namespace detail
{

BOOST_SPIRIT_TERMINAL(string_generator)

}   // namespace detail
}   // namespace json
}   // namespace missio

namespace boost
{
namespace spirit
{

template <>
struct use_terminal<karma::domain, missio::json::detail::tag::string_generator> : mpl::true_
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

struct any_string_generator : boost::spirit::karma::primitive_generator<any_string_generator>
{
    template <typename Context, typename Unused>
    struct attribute
    {
        typedef string type;
    };

    template <typename OutputIterator, typename Context, typename Delimiter, typename Attribute>
    static bool generate(OutputIterator& sink, Context& context, Delimiter const& d, Attribute const& attr)
    {
        if(!boost::spirit::traits::has_optional_value(attr))
            return false;

        return string_inserter::call(sink, boost::spirit::traits::extract_from<string>(attr, context)) && boost::spirit::karma::delimit_out(sink, d);
    }

    template <typename OutputIterator, typename Context, typename Delimiter>
    static bool generate(OutputIterator&, Context&, Delimiter const&, boost::spirit::unused_type)
    {
        BOOST_SPIRIT_ASSERT_MSG(false, json_string_generator_not_usable_without_attribute, ());
        return false;
    }

    template <typename Context>
    static boost::spirit::info what(Context const& /*context*/)
    {
        return boost::spirit::info("json-string-generator");
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

namespace boost
{
namespace spirit
{
namespace karma
{

template <typename Modifiers>
struct make_primitive<missio::json::detail::tag::string_generator, Modifiers>
{
    typedef missio::json::detail::any_string_generator result_type;

    result_type operator()(unused_type, unused_type) const
    {
        return result_type();
    }
};

}   // namespace karma
}   // namespace spirit
}   // namespace boost

#endif  // _missio_json_detail_string_generator_hpp
