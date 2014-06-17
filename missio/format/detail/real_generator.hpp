//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_real_generator_hpp
#define _missio_format_detail_real_generator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/real_policies.hpp>
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
struct default_real_generator
{
    typedef boost::spirit::karma::real_generator<T, default_real_policies<T>> type;

    static type const& get()
    {
        static type generator;
        return generator;
    }
};

template <typename T, real_format Format = real_format::general>
struct real_generator
{
    typedef boost::spirit::karma::real_generator<T, real_policies<T, Format>> type;

    static type make(int precision, bool force_sign, bool upper_case)
    {
        return type(real_policies<T, Format>(precision, force_sign, upper_case));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_real_generator_hpp
