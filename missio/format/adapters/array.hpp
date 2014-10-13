//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_array_hpp
#define _missio_format_adapters_array_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <cstddef>
#include <iostream>


namespace missio
{
namespace format
{
namespace detail
{

template <typename T, size_t N>
struct type_adapter<T[N]>
{
    template <typename Sink>
    static void format(Sink& sink, T const value[N])
    {
        write(sink, '[', value[0]);

        for(std::size_t i = 1; i < N; ++i)
        {
            write(sink, ',', ' ', value[i]);
        }

        write(sink, ']');
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_array_hpp
