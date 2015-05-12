//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_pointer_hpp
#define _missio_format_adapters_pointer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/inserters_impl.hpp>

// STL headers
#include <cstddef>
#include <cstdint>


namespace missio
{
namespace format
{
namespace detail
{

template <typename T>
struct type_adapter<T*>
{
    template <typename Sink>
    static void format(Sink& sink, T const* value)
    {
        if(value)
        {
            write(sink, *value);
        }
        else
        {
            write(sink, nullptr);
        }
    }
};

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
        if(value)
        {
            write(sink, "0x", hex(value));
        }
        else
        {
            write(sink, nullptr);
        }
    }
};

template <>
struct type_adapter<std::nullptr_t>
{
    template <typename Sink>
    static void format(Sink& sink, std::nullptr_t)
    {
        write(sink, "(null)");
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_pointer_hpp
