//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_inserters_impl_hpp
#define _missio_format_inserters_impl_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/type_inserter.hpp>
#include <missio/format/detail/group_value.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value>
auto bin(Value const& value, int precision = -1, bool force_sign = false)
{
    return make_group_value(value, int_inserter<2>(precision, force_sign));
}

template <typename Value>
auto oct(Value const& value, int precision = -1, bool force_sign = false)
{
    return make_group_value(value, int_inserter<8>(precision, force_sign));
}

template <typename Value>
auto dec(Value const& value, int precision = -1, bool force_sign = false)
{
    return make_group_value(value, int_inserter<10>(precision, force_sign));
}

template <typename Value>
auto hex(Value const& value, int precision = -1, bool upper_case = false, bool force_sign = false)
{
    return make_group_value(value, int_inserter<16>(precision, force_sign, upper_case));
}

template <typename Value>
auto fixed(Value const& value, int precision = -1, bool force_sign = false)
{
    return make_group_value(value, real_inserter<real_format::fixed>(precision, force_sign));
}

template <typename Value>
auto real(Value const& value, int precision = -1, bool upper_case = false, bool force_sign = false)
{
    return make_group_value(value, real_inserter<real_format::general>(precision, force_sign, upper_case));
}

template <typename Value>
auto scientific(Value const& value, int precision = -1, bool upper_case = false, bool force_sign = false)
{
    return make_group_value(value, real_inserter<real_format::scientific>(precision, force_sign, upper_case));
}

template <typename Value>
auto align(Value const& value, int align)
{
    return make_group_value(value, align_inserter(align));
}

template <typename Value>
auto repeat(Value const& value, unsigned int count)
{
    return make_group_value(value, repeat_inserter(count));
}

template <typename Value>
auto lower(Value const& value)
{
    return make_group_value<lower_case_inserter>(value);
}

template <typename Value>
auto upper(Value const& value)
{
    return make_group_value<upper_case_inserter>(value);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_inserters_impl_hpp
