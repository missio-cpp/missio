//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_pointer_hpp
#define _missio_format_adapters_pointer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/config.hpp>

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

#if defined(BOOST_WINDOWS)

    template <typename Sink>
    static void format(Sink& sink, std::uintptr_t const& value)
    {
        write(sink, hex(value, 2 * sizeof(value), true));
    }

#else   // !defined(BOOST_WINDOWS)

    template <typename Sink>
    static void format(Sink& sink, std::uintptr_t const& value)
    {
        write(sink, '0');

        if(value)
            write(sink, 'x', hex(value));
    }

#endif  // defined(BOOST_WINDOWS)
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_pointer_hpp
