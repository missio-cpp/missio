//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_type_adapter_hpp
#define _missio_format_detail_type_adapter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/generate_value.hpp>
#include <missio/format/detail/real_generator.hpp>
#include <missio/format/detail/group_value.hpp>
#include <missio/format/detail/string_view.hpp>

// BOOST headers
#include <missio/common/boost_spirit_karma.hpp>

// STL headers
#include <algorithm>
#include <cstddef>
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value, typename Enable = void>
struct type_adapter
{
    template <typename Sink>
    static void format(Sink& sink, Value const& value)
    {
        generate_value(sink, value, boost::spirit::stream);
    }
};

template <typename Value>
struct type_adapter<Value const> : type_adapter<Value>
{
};

template <typename Value>
struct type_adapter<Value const*> : type_adapter<Value*>
{
};

template <typename Value, typename Inserter>
struct type_adapter<group_value<Value, Inserter>>
{
    template <typename Sink>
    static void format(Sink& sink, group_value<Value, Inserter> const& value)
    {
        value.inserter().call(sink, value.value());
    }
};

template <>
struct type_adapter<bool>
{
    template <typename Sink>
    static void format(Sink& sink, bool value)
    {
        generate_value(sink, value, boost::spirit::bool_);
    }
};

template <>
struct type_adapter<unsigned char>
{
    template <typename Sink>
    static void format(Sink& sink, unsigned char value)
    {
        generate_value(sink, value, boost::spirit::ushort_);
    }
};

template <>
struct type_adapter<signed char>
{
    template <typename Sink>
    static void format(Sink& sink, signed char value)
    {
        generate_value(sink, value, boost::spirit::short_);
    }
};

template <>
struct type_adapter<unsigned short>
{
    template <typename Sink>
    static void format(Sink& sink, unsigned short value)
    {
        generate_value(sink, value, boost::spirit::ushort_);
    }
};

template <>
struct type_adapter<short>
{
    template <typename Sink>
    static void format(Sink& sink, short value)
    {
        generate_value(sink, value, boost::spirit::short_);
    }
};

template <>
struct type_adapter<unsigned int>
{
    template <typename Sink>
    static void format(Sink& sink, unsigned int value)
    {
        generate_value(sink, value, boost::spirit::uint_);
    }
};

template <>
struct type_adapter<int>
{
    template <typename Sink>
    static void format(Sink& sink, int value)
    {
        generate_value(sink, value, boost::spirit::int_);
    }
};

template <>
struct type_adapter<unsigned long>
{
    template <typename Sink>
    static void format(Sink& sink, unsigned long value)
    {
        generate_value(sink, value, boost::spirit::ulong_);
    }
};


template <>
struct type_adapter<long>
{
    template <typename Sink>
    static void format(Sink& sink, long value)
    {
        generate_value(sink, value, boost::spirit::long_);
    }
};

template <>
struct type_adapter<unsigned long long>
{
    template <typename Sink>
    static void format(Sink& sink, unsigned long long value)
    {
        generate_value(sink, value, boost::spirit::ulong_long);
    }
};

template <>
struct type_adapter<long long>
{
    template <typename Sink>
    static void format(Sink& sink, long long value)
    {
        generate_value(sink, value, boost::spirit::long_long);
    }
};

template <>
struct type_adapter<float>
{
    template <typename Sink>
    static void format(Sink& sink, float value)
    {
        generate_value(sink, value, float_generator);
    }
};

template <>
struct type_adapter<double>
{
    template <typename Sink>
    static void format(Sink& sink, double value)
    {
        generate_value(sink, value, double_generator);
    }
};

template <>
struct type_adapter<long double>
{
    template <typename Sink>
    static void format(Sink& sink, long double value)
    {
        generate_value(sink, value, long_double_generator);
    }
};

template <>
struct type_adapter<char>
{
    template <typename Sink>
    static void format(Sink& sink, char value)
    {
        generate_value(sink, value, boost::spirit::standard::char_);
    }
};

template <>
struct type_adapter<wchar_t>
{
    template <typename Sink>
    static void format(Sink& sink, char value)
    {
        generate_value(sink, value, boost::spirit::standard_wide::char_);
    }
};

template <>
struct type_adapter<char*>
{
    template <typename Sink>
    static void format(Sink& sink, char const* value)
    {
        generate_value(sink, value, boost::spirit::standard::string);
    }
};

template <>
struct type_adapter<char const*> : type_adapter<char*>
{
};

template <std::size_t N>
struct type_adapter<char[N]> : type_adapter<char*>
{
};

template <std::size_t N>
struct type_adapter<char const[N]> : type_adapter<char*>
{
};

template <std::size_t N>
struct type_adapter<char(&)[N]> : type_adapter<char*>
{
};

template <std::size_t N>
struct type_adapter<char const(&)[N]> : type_adapter<char*>
{
};

template <>
struct type_adapter<wchar_t*>
{
    template <typename Sink>
    static void format(Sink& sink, wchar_t const* value)
    {
        generate_value(sink, value, boost::spirit::standard_wide::string);
    }
};

template <>
struct type_adapter<wchar_t const*> : type_adapter<wchar_t*>
{
};

template <std::size_t N>
struct type_adapter<wchar_t[N]> : type_adapter<wchar_t*>
{
};

template <std::size_t N>
struct type_adapter<wchar_t const[N]> : type_adapter<wchar_t*>
{
};

template <std::size_t N>
struct type_adapter<wchar_t(&)[N]> : type_adapter<wchar_t*>
{
};

template <std::size_t N>
struct type_adapter<wchar_t const(&)[N]> : type_adapter<wchar_t*>
{
};

template <>
struct type_adapter<std::string>
{
    template <typename Sink>
    static void format(Sink& sink, std::string const& value)
    {
        generate_value(sink, value, boost::spirit::standard::string);
    }
};

template <>
struct type_adapter<std::wstring>
{
    template <typename Sink>
    static void format(Sink& sink, std::wstring const& value)
    {
        generate_value(sink, value, boost::spirit::standard_wide::string);
    }
};

template <typename Char, typename Traits>
struct type_adapter<basic_string_view<Char, Traits>>
{
    template <typename Sink>
    static void format(Sink& sink, basic_string_view<Char, Traits> const& value)
    {
        std::copy(std::begin(value), std::end(value), sink_iterator<Sink>(sink));
    }
};

template <>
struct type_adapter<sink_buffer>
{
    template <typename Sink>
    static void format(Sink& sink, sink_buffer const& value)
    {
        std::copy(std::begin(value), std::end(value), sink_iterator<Sink>(sink));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_type_adapter_hpp
