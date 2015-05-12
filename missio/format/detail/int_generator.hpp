//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_int_generator_hpp
#define _missio_format_detail_int_generator_hpp

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
namespace tag
{

template <typename T, unsigned int Radix>
struct int_generator
{
    BOOST_SPIRIT_IS_TAG()
};

}   // namespace tag

template <typename T = int, unsigned int Radix = 10>
struct int_generator : boost::spirit::terminal<tag::int_generator<T, Radix>>
{
};

}   // namespace detail
}   // namespace format
}   // namespace missio

namespace boost
{
namespace spirit
{

template <typename T, unsigned int Radix, typename A0, typename A1, typename A2>
struct use_terminal<karma::domain, terminal_ex<missio::format::detail::tag::int_generator<T, Radix>, fusion::vector3<A0, A1, A2>>> : mpl::true_
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

template <typename T, unsigned int Radix>
struct any_int_generator : boost::spirit::karma::primitive_generator<any_int_generator<T, Radix>>
{
    typedef boost::mpl::int_<
        boost::spirit::karma::generator_properties::countingbuffer
    > properties;

    template <typename Context, typename Unused = boost::spirit::unused_type>
    struct attribute
    {
        typedef T type;
    };

    any_int_generator(int precision, bool force_sign, bool upper_case) :
        precision_(precision),
        force_sign_(force_sign),
        upper_case_(upper_case)
    {
    }

    any_int_generator(any_int_generator const&) = default;
    any_int_generator& operator=(any_int_generator const&) = delete;

    template <typename OutputIterator, typename Context, typename Delimiter, typename Attribute>
    bool generate(OutputIterator& sink, Context& context, Delimiter const& d, Attribute const& attr) const
    {
        if (!boost::spirit::traits::has_optional_value(attr))
            return false;

        return generate(sink, boost::spirit::traits::extract_from<T>(attr, context)) && boost::spirit::karma::delimit_out(sink, d);
    }

    template <typename Context>
    static boost::spirit::info what(Context const& /*context*/)
    {
        return boost::spirit::info("int-generator");
    }

private:
    template <typename OutputIterator, typename Attribute>
    bool generate(OutputIterator& sink, Attribute const& attr) const
    {
        using boost::spirit::karma::detail::enable_counting;
        using boost::spirit::karma::detail::disable_counting;
        using boost::spirit::karma::detail::enable_buffering;

        if(!insert_sign(sink, attr))
            return false;

        if(precision_ > 0)
        {
            bool result = false;

            enable_buffering<OutputIterator> buffering(sink, precision_);

            {
                disable_counting<OutputIterator> nocounting(sink);
                result = insert_int(sink, attr);
            }

            buffering.disable();

            enable_counting<OutputIterator> counting(sink, buffering.buffer_size());

            while(result && static_cast<int>(counting.count()) < precision_)
            {
                result = boost::spirit::karma::generate(sink, '0');
            }

            if(result)
            {
                buffering.buffer_copy();
            }

            return result;
        }

        return insert_int(sink, attr);
    }

    template <typename OutputIterator, typename Attribute>
    bool insert_sign(OutputIterator& sink, Attribute const& attr) const
    {
        bool const is_zero = boost::spirit::traits::test_zero(attr);
        bool const is_negative = boost::spirit::traits::test_negative(attr);

        return boost::spirit::karma::sign_inserter::call(sink, is_zero, is_negative, force_sign_);
    }

    template <typename Encoding, typename Tag>
    struct int_inserter
    {
        typedef boost::spirit::karma::int_inserter<Radix, Encoding, Tag> type;

        template <typename OutputIterator, typename Attribute>
        static bool call(OutputIterator& sink, Attribute const& attr)
        {
            return type::call(sink, boost::spirit::traits::get_absolute_value(attr));
        }
    };

    template <typename OutputIterator, typename Attribute>
    bool insert_int(OutputIterator& sink, Attribute const& attr) const
    {
        if(!upper_case_)
        {
            return int_inserter<boost::spirit::unused_type, boost::spirit::unused_type>::call(sink, attr);
        }

        return int_inserter<boost::spirit::char_encoding::ascii, boost::spirit::tag::upper>::call(sink, attr);
    }

private:
    int const precision_;
    bool const force_sign_;
    bool const upper_case_;
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

template <typename T, unsigned int Radix, typename A0, typename A1, typename A2, typename Modifiers>
struct make_primitive<terminal_ex<missio::format::detail::tag::int_generator<T, Radix>, fusion::vector3<A0, A1, A2>>, Modifiers>
{
    typedef missio::format::detail::any_int_generator<T, Radix> result_type;

    template <typename Terminal>
    result_type operator()(Terminal const& term, unused_type) const
    {
        return result_type(fusion::at_c<0>(term.args), fusion::at_c<1>(term.args), fusion::at_c<2>(term.args));
    }
};

}   // namespace karma
}   // namespace spirit
}   // namespace boost

#endif  // _missio_format_detail_int_generator_hpp
