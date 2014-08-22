//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_write_impl_hpp
#define _missio_format_detail_write_impl_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_traits.hpp>
#include <missio/format/detail/type_adapter.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
void write_impl(Sink& /*sink*/)
{
}

template <typename Sink, typename Value, typename ... Args>
void write_impl(Sink& sink, Value const& value, Args const& ... args)
{
    type_adapter<Value>::format(sink, value);

    write_impl(sink, args...);
}

template <typename Sink, typename ... Args>
void write(Sink& sink, Args const& ... args)
{
    typename traits::sink_traits<Sink>::adapter_type sink_adapter(sink);

    write_impl(sink_adapter, args...);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_write_impl_hpp
