//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_pointer_hpp
#define _missio_format_adapters_pointer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/inserters.hpp>

// STL headers
#include <cstddef>
#include <cstdint>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<void*>
{
    template <typename Sink>
    static void format(Sink& sink, void const* value)
    {
        write_pointer(sink, reinterpret_cast<std::uintptr_t>(value));
    }

    template <typename Sink>
    static void write_pointer(Sink& sink, std::uintptr_t value)
    {
        write(sink, '0');

        if(value)
            write(sink, 'x', hex(value));
    }
};

template <>
struct type_adapter<std::nullptr_t>
{
    template <typename Sink>
    static void format(Sink& sink, std::nullptr_t const& value)
    {
        write(sink, '0');
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_pointer_hpp
