//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_real_policies_hpp
#define _missio_format_detail_real_policies_hpp

// Application headers
#include <missio/format/detail/real_format.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename T>
struct default_real_policies : boost::spirit::karma::real_policies<T>
{
    static unsigned int precision(T)
    {
        return 6;
    }
};

template <typename T, real_format Format>
class real_policies :
    public boost::spirit::karma::real_policies<T>
{
public:
    typedef boost::spirit::karma::real_policies<T> base_policy_type;

public:
    real_policies(int precision, bool force_sign, bool upper_case) :
        precision_(precision),
        force_sign_(force_sign),
        upper_case_(upper_case)
    {
    }

    real_policies(real_policies const& other) :
        precision_(other.precision_),
        force_sign_(other.force_sign_),
        upper_case_(other.upper_case_)
    {
    }

    bool force_sign(T) const
    {
        return force_sign_;
    }

    bool trailing_zeros(T) const
    {
        return precision_ > 0;
    }

    int floatfield(T n) const
    {
        switch(Format)
        {
            case real_format::scientific:
                return base_policy_type::fmtflags::scientific;

            case real_format::fixed:
                return base_policy_type::fmtflags::fixed;

            default:
                return base_policy_type::floatfield(n);
        }
    }

    unsigned int precision(T) const
    {
        return precision_ >= 0 ? precision_ : 6;
    }

    template <typename OutputIterator>
    static bool dot(OutputIterator& sink, T n, unsigned int precision) 
    {
        return precision > 0 ? base_policy_type::dot(sink, n, precision) : true;
    }

    template <typename CharEncoding, typename Tag, typename OutputIterator>
    bool exponent(OutputIterator& sink, long n) const
    {
        using boost::spirit::tag::upper;
        using boost::spirit::char_encoding::ascii;

        if(upper_case_)
            return base_policy_type::template exponent<ascii, upper>(sink, n);

        return base_policy_type::template exponent<CharEncoding, Tag>(sink, n);
    }

private:
    // prevent MSVC warning C4512: assignment operator could not be generated
    real_policies& operator=(real_policies const& other);

private:
    int const precision_;
    bool const force_sign_;
    bool const upper_case_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_real_policies_hpp