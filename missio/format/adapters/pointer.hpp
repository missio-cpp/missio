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
        format(sink, reinterpret_cast<std::uintptr_t>(value));
    }

#if defined(_WIN32) || defined(_WIN64)

    template <typename Sink>
    static void format(Sink& sink, std::uintptr_t const& value)
    {
        write(sink, hex(value, 2 * sizeof(value), true));
    }

#else

    template <typename Sink>
    static void format(Sink& sink, std::uintptr_t const& value)
    {
        write(sink, '0');

        if(value)
            write(sink, 'x', hex(value));
    }

#endif
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_pointer_hpp
