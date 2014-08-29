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
#include <missio/format/detail/type_adapter.hpp>
#include <missio/format/detail/format_traits.hpp>
#include <missio/format/detail/insert_string.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <std::uint32_t N = 0, typename Sink>
void insert(Sink& /*sink*/, std::uint32_t const /*index*/)
{
}

template <std::uint32_t N = 0, typename Sink, typename Value, typename ... Args>
void insert(Sink& sink, std::uint32_t const index, Value const& value, Args const& ... args)
{
    if(N == index)
        type_adapter<Value>::format(sink, value);
    else
        insert<N + 1>(sink, index, args...);
}

template <typename Sink, typename Format, typename ... Args>
void print(Sink& sink, Format const& format, Args const& ... args)
{
    typename traits::sink_traits<Sink>::adapter_type sink_adapter(sink);
    typename traits::format_traits<Format>::adapter_type format_adapter(format);

    for(format_item const& item : format_adapter.items())
    {
        insert(sink_adapter, item.index, args...);
        insert_string(sink_adapter, item.string);
    }
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_print_impl_hpp
