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
group_value<Value, detail::int_inserter<2>> bin(Value const& value, int precision = -1, bool force_sign = false)
{
    return group_value<Value, int_inserter<2>>(value, int_inserter<2>(precision, force_sign));
}

template <typename Value>
group_value<Value, int_inserter<8>> oct(Value const& value, int precision = -1, bool force_sign = false)
{
    return group_value<Value, int_inserter<8>>(value, int_inserter<8>(precision, force_sign));
}

template <typename Value>
group_value<Value, int_inserter<10>> dec(Value const& value, int precision = -1, bool force_sign = false)
{
    return group_value<Value, int_inserter<10>>(value, int_inserter<10>(precision, force_sign));
}

template <typename Value>
group_value<Value, int_inserter<16>> hex(Value const& value, int precision = -1, bool upper_case = false, bool force_sign = false)
{
    return group_value<Value, int_inserter<16>>(value, int_inserter<16>(precision, force_sign, upper_case));
}

template <typename Value>
group_value<Value, real_inserter<real_format::fixed>> fixed(Value const& value, int precision = -1, bool force_sign = false)
{
    return group_value<Value, real_inserter<real_format::fixed>>(value, real_inserter<real_format::fixed>(precision, force_sign));
}

template <typename Value>
group_value<Value, real_inserter<real_format::general>> real(Value const& value, int precision = -1, bool upper_case = false, bool force_sign = false)
{
    return group_value<Value, real_inserter<real_format::general>>(value, real_inserter<real_format::general>(precision, force_sign, upper_case));
}

template <typename Value>
group_value<Value, real_inserter<real_format::scientific>> scientific(Value const& value, int precision = -1, bool upper_case = false, bool force_sign = false)
{
    return group_value<Value, real_inserter<real_format::scientific>>(value, real_inserter<real_format::scientific>(precision, force_sign, upper_case));
}

template <typename Value>
group_value<Value, align_inserter> align(Value const& value, int align)
{
    return group_value<Value, align_inserter>(value, align_inserter(align));
}

template <typename Value>
group_value<Value, repeat_inserter> repeat(Value const& value, unsigned int count)
{
    return group_value<Value, repeat_inserter>(value, repeat_inserter(count));
}

template <typename Value>
group_value<Value, lower_case_inserter> lower(Value const& value)
{
    return group_value<Value, lower_case_inserter>(value);
}

template <typename Value>
group_value<Value, upper_case_inserter> upper(Value const& value)
{
    return group_value<Value, upper_case_inserter>(value);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_inserters_impl_hpp
