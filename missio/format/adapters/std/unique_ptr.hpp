//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_unique_ptr_hpp
#define _missio_format_adapters_std_unique_ptr_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/adapters/pointer.hpp>

// STL headers
#include <memory>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value>
struct type_adapter<std::unique_ptr<Value>>
{
    template <typename Sink>
    static void format(Sink& sink, std::unique_ptr<Value> const& value)
    {
        write(sink, value.get());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_unique_ptr_hpp
