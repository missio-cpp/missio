//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_inserters_hpp
#define _missio_format_inserters_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/inserters_impl.hpp>


namespace missio
{
namespace format
{

template <typename Value>
auto bin(Value const& value,
         int precision = -1,
         bool force_sign = false) -> decltype(detail::bin(value, precision, force_sign))
{
    return detail::bin(value, precision, force_sign);
}

template <typename Value>
auto oct(Value const& value,
         int precision = -1,
         bool force_sign = false) -> decltype(detail::oct(value, precision, force_sign))
{
    return detail::oct(value, precision, force_sign);
}

template <typename Value>
auto dec(Value const& value,
         int precision = -1,
         bool force_sign = false) -> decltype(detail::dec(value, precision, force_sign))
{
    return detail::dec(value, precision, force_sign);
}

template <typename Value>
auto hex(Value const& value,
         int precision = -1,
         bool upper_case = false,
         bool force_sign = false) -> decltype(detail::hex(value, precision, upper_case, force_sign))
{
    return detail::hex(value, precision, upper_case, force_sign);
}

template <typename Value>
auto fixed(Value const& value,
           int precision = -1,
           bool force_sign = false) -> decltype(detail::fixed(value, precision, force_sign))
{
    return detail::fixed(value, precision, force_sign);
}

template <typename Value>
auto real(Value const& value,
          int precision = -1,
          bool upper_case = false,
          bool force_sign = false) -> decltype(detail::real(value, precision, upper_case, force_sign))
{
    return detail::real(value, precision, upper_case, force_sign);
}

template <typename Value>
auto scientific(Value const& value,
                int precision = -1,
                bool upper_case = false,
                bool force_sign = false) -> decltype(detail::scientific(value, precision, upper_case, force_sign))
{
    return detail::scientific(precision, upper_case, force_sign);
}

template <typename Value>
auto align(Value const& value, int align) -> decltype(detail::align(value, align))
{
    return detail::align(value, align);
}

template <typename Value>
auto repeat(Value const& value, unsigned int count) -> decltype(detail::repeat(value, count))
{
    return detail::repeat(value, count);
}

template <typename Value>
auto lower(Value const& value) -> decltype(detail::lower(value))
{
    return detail::lower(value);
}

template <typename Value>
auto upper(Value const& value) -> decltype(detail::upper(value))
{
    return detail::upper(value);
}

}   // namespace format
}   // namespace missio

#endif  // _missio_format_inserters_hpp
