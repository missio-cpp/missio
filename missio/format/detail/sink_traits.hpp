//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_traits_hpp
#define _missio_format_detail_sink_traits_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_iterator.hpp>
#include <missio/format/detail/sink_adapter.hpp>
#include <missio/format/detail/sink_buffer.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
struct sink_traits
{
    typedef detail::sink_adapter<Sink> adapter_type;
};

template <typename Sink>
struct sink_traits<detail::sink_adapter<Sink>>
{
    typedef detail::sink_adapter<Sink>& adapter_type;
};

template <typename Sink, typename Policy>
struct sink_traits<detail::sink_iterator<Sink, Policy>>
{
    typedef detail::sink_iterator<Sink, Policy>& adapter_type;
};

template <>
struct sink_traits<detail::sink_buffer>
{
    typedef detail::sink_buffer& adapter_type;
};

template <typename Sink>
using sink_adapter_type = typename sink_traits<Sink>::adapter_type;

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_traits_hpp
