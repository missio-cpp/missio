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
#include <missio/format/detail/sink_adapter.hpp>
#include <missio/format/detail/sink_buffer.hpp>


namespace missio
{
namespace format
{
namespace traits
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

template <>
struct sink_traits<detail::sink_buffer>
{
    typedef detail::sink_buffer& adapter_type;
};

}   // namespace traits
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_traits_hpp
