//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_pair_hpp
#define _missio_format_adapters_std_pair_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <utility>


namespace missio
{
namespace format
{
namespace detail
{

template <typename T1, typename T2>
struct type_adapter<std::pair<T1, T2>>
{
    template <typename Sink>
    static void format(Sink& sink, std::pair<T1, T2> const& value)
    {
        write(sink, '(', value.first, ", ", value.second, ')');
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_pair_hpp
