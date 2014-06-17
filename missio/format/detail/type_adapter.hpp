//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_type_adapter_hpp
#define _missio_format_detail_type_adapter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/type_generator.hpp>
#include <missio/format/detail/generate_value.hpp>
#include <missio/format/detail/group_value.hpp>


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
        generate_value(sink, value, type_generator<Value>::get());
    }
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

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_type_adapter_hpp
