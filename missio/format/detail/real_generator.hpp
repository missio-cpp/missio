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

template <typename T, real_format Format>
auto make_real_generator(int precision, bool force_sign, bool upper_case)
{
    return boost::spirit::karma::real_generator<T, real_policies<T, Format>>{{precision, force_sign, upper_case}};
}

template <typename T>
auto make_default_real_generator()
{
    return boost::spirit::karma::real_generator<T, default_real_policies<T>>{};
}

auto const float_generator = make_default_real_generator<float>();
auto const double_generator = make_default_real_generator<double>();
auto const long_double_generator = make_default_real_generator<long double>();

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_real_generator_hpp
