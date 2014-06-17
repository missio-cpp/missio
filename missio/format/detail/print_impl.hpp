//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_print_impl_hpp
#define _missio_format_detail_print_impl_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_traits.hpp>
#include <missio/format/detail/format_traits.hpp>
#include <missio/format/detail/format_value.hpp>
#include <missio/format/detail/insert_string.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <unsigned int N = 0, typename Sink>
void insert_impl(Sink& sink, unsigned int index)
{
}

template <unsigned int N = 0, typename Sink, typename Value, typename ... Args>
void insert_impl(Sink& sink, unsigned int index, Value const& value, Args const& ... args)
{
    if(N == index)
        format_value(sink, value);
    else
        insert_impl<N + 1>(sink, index, args...);
}

template <typename Sink, typename ... Args>
void insert(Sink& sink, unsigned int index, Args const& ... args)
{
    insert_impl<>(sink, index, args...);
}

template <typename Sink, typename Format, typename ... Args>
void print_impl(Sink& sink, Format const& format, Args const& ... args)
{
    for(auto const& item : format.items())
    {
        insert(sink, item.index, args...);
        insert_string(sink, item.string);
    }
}

template <typename Sink, typename Format, typename ... Args>
void print(Sink& sink, Format const& format, Args const& ... args)
{
    typename traits::sink_traits<Sink>::adapter_type sink_adapter(sink);
    typename traits::format_traits<Format>::adapter_type format_adapter(format);

    print_impl(sink_adapter, format_adapter, args...);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_print_impl_hpp
