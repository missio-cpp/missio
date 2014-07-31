//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_repeat_directive_hpp
#define _missio_format_detail_repeat_directive_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace missio
{
namespace format
{
namespace detail
{

BOOST_SPIRIT_TERMINAL_EX(repeat_directive)

}   // namespace detail
}   // namespace format
}   // namespace missio

namespace boost
{
namespace spirit
{

template <>
struct use_directive<karma::domain, terminal_ex<missio::format::detail::tag::repeat_directive, fusion::vector1<unsigned int>>> : mpl::true_
{
};

template <>
struct use_lazy_directive<karma::domain, missio::format::detail::tag::repeat_directive, 1> : mpl::true_
{
};

}   // namespace spirit
}   // namespace boost

namespace missio
{
namespace format
{
namespace detail
{

template <typename Subject>
struct repeat_generator : boost::spirit::karma::primitive_generator<repeat_generator<Subject>>
{
    typedef Subject subject_type;

    typedef typename subject_type::properties properties;

    template <typename Context, typename Iterator = boost::spirit::unused_type>
    struct attribute : boost::spirit::traits::attribute_of<subject_type, Context, Iterator>
    {
    };

    repeat_generator(Subject const& subject, unsigned int count) :
        subject_(subject),
        count_(count)
    {
    }

    repeat_generator(repeat_generator const&) = default;
    repeat_generator& operator=(repeat_generator const&) = delete;

    template <typename OutputIterator, typename Context, typename Delimiter, typename Attribute>
    bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d, Attribute const& attr) const
    {
        bool result = true;
        unsigned int i = count_;

        while(result && i-- > 0)
            result = subject_.generate(sink, ctx, d, attr);

        return result;
    }

    template <typename Context>
    boost::spirit::info what(Context const& context) const
    {
        return boost::spirit::info("repeat-directive", subject_.what(context));
    }

private:
    Subject subject_;
    unsigned int count_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

namespace boost
{
namespace spirit
{
namespace karma
{

template <typename Subject, typename Modifiers>
struct make_directive<terminal_ex<missio::format::detail::tag::repeat_directive, fusion::vector1<unsigned int>>, Subject, Modifiers>
{
    typedef missio::format::detail::repeat_generator<Subject> result_type;

    template <typename Terminal>
    result_type operator()(Terminal const& term, Subject const& subject, unused_type) const
    {
        return result_type(subject, fusion::at_c<0>(term.args));
    }
};

}   // namespace karma
}   // namespace spirit
}   // namespace boost

namespace boost
{
namespace spirit
{
namespace traits
{

template <typename Subject>
struct has_semantic_action<missio::format::detail::repeat_generator<Subject>> : has_semantic_action<Subject>
{
};

}   // namespace traits
}   // namespace spirit
}   // namespace boost

#endif  // _missio_format_detail_repeat_directive_hpp
