//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_value_hpp
#define _missio_format_detail_format_value_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/type_adapter.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink, typename Value>
void format_value(Sink& sink, Value const& value)
{
    type_adapter<Value>::format(sink, value);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_value_hpp
