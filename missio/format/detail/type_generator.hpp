//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_type_generator_hpp
#define _missio_format_detail_type_generator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/real_generator.hpp>
#include <missio/format/detail/sink_buffer.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/utility/string_ref.hpp>

// STL headers
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Type>
struct type_generator
{
    typedef boost::spirit::stream_type const& type;
    static type get() { return boost::spirit::stream; }
};

template <typename Type>
struct type_generator<Type const> : type_generator<Type>
{
};

template <>
struct type_generator<bool>
{
    typedef boost::spirit::bool_type const& type;
    static type get() { return boost::spirit::bool_; }
};

template <>
struct type_generator<unsigned char>
{
    typedef boost::spirit::ushort_type const& type;
    static type get() { return boost::spirit::ushort_; }
};

template <>
struct type_generator<short>
{
    typedef boost::spirit::short_type const& type;
    static type get() { return boost::spirit::short_; }
};

template <>
struct type_generator<unsigned short>
{
    typedef boost::spirit::ushort_type const& type;
    static type get() { return boost::spirit::ushort_; }
};

template <>
struct type_generator<int>
{
    typedef boost::spirit::int_type const& type;
    static type get() { return boost::spirit::int_; }
};

template <>
struct type_generator<unsigned int>
{
    typedef boost::spirit::uint_type const& type;
    static type get() { return boost::spirit::uint_; }
};

template <>
struct type_generator<long>
{
    typedef boost::spirit::long_type const& type;
    static type get() { return boost::spirit::long_; }
};

template <>
struct type_generator<unsigned long>
{
    typedef boost::spirit::ulong_type const& type;
    static type get() { return boost::spirit::ulong_; }
};

template <>
struct type_generator<long long>
{
    typedef boost::spirit::long_long_type const& type;
    static type get() { return boost::spirit::long_long; }
};

template <>
struct type_generator<unsigned long long>
{
    typedef boost::spirit::ulong_long_type const& type;
    static type get() { return boost::spirit::ulong_long; }
};

template <>
struct type_generator<float>
{
    typedef default_real_generator<float>::type const& type;
    static type get() { return default_real_generator<float>::get(); }
};

template <>
struct type_generator<double>
{
    typedef default_real_generator<double>::type const& type;
    static type get() { return default_real_generator<double>::get(); }
};

template <>
struct type_generator<long double>
{
    typedef default_real_generator<long double>::type const& type;
    static type get() { return default_real_generator<long double>::get(); }
};

template <>
struct type_generator<char>
{
    typedef boost::spirit::standard::char_type const& type;
    static type get() { return boost::spirit::standard::char_; }
};

template <>
struct type_generator<wchar_t>
{
    typedef boost::spirit::standard_wide::char_type const& type;
    static type get() { return boost::spirit::standard_wide::char_; }
};

template <>
struct type_generator<char*>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <>
struct type_generator<wchar_t*>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <>
struct type_generator<char const*>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <>
struct type_generator<wchar_t const*>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <std::size_t N>
struct type_generator<char[N]>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <std::size_t N>
struct type_generator<wchar_t[N]>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <std::size_t N>
struct type_generator<char const[N]>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <std::size_t N>
struct type_generator<wchar_t const[N]>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <std::size_t N>
struct type_generator<char(&)[N]>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <std::size_t N>
struct type_generator<wchar_t(&)[N]>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <std::size_t N>
struct type_generator<char const(&)[N]>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <std::size_t N>
struct type_generator<wchar_t const(&)[N]>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <>
struct type_generator<std::string>
{
    typedef boost::spirit::standard::string_type const& type;
    static type get() { return boost::spirit::standard::string; }
};

template <>
struct type_generator<std::wstring>
{
    typedef boost::spirit::standard_wide::string_type const& type;
    static type get() { return boost::spirit::standard_wide::string; }
};

template <>
struct type_generator<boost::string_ref>
{
    typedef boost::spirit::auto_type const& type;
    static type get() { return boost::spirit::auto_; }
};

template <>
struct type_generator<boost::wstring_ref>
{
    typedef boost::spirit::auto_type const& type;
    static type get() { return boost::spirit::auto_; }
};

template <typename Iterator>
struct type_generator<boost::iterator_range<Iterator>>
{
    typedef boost::spirit::auto_type const& type;
    static type get() { return boost::spirit::auto_; }
};

template <>
struct type_generator<sink_buffer>
{
    typedef boost::spirit::auto_type const& type;
    static type get() { return boost::spirit::auto_; }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_type_generator_hpp
