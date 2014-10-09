//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_tuple_hpp
#define _missio_format_adapters_std_tuple_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <tuple>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<std::tuple<>>
{
    template <typename Sink>
    static void format(Sink& sink, std::tuple<> const& /*value*/)
    {
        write(sink, "()");
    }
};

template <typename ... Types>
struct type_adapter<std::tuple<Types...>>
{
    template <std::size_t I = sizeof...(Types) - 1>
    using index = std::integral_constant<std::size_t, I>;

    template <typename Sink>
    static void format(Sink& sink, std::tuple<Types...> const& value)
    {
        write(sink, '(');

        write_tuple(sink, value, index<>{});

        write(sink, ')');
    }

    template <typename Sink, std::size_t I>
    static void write_tuple(Sink& sink, std::tuple<Types...> const& value, index<I>)
    {
        write_tuple(sink, value, index<I - 1>{});
        write(sink, ", ", std::get<I>(value));
    }

    template <typename Sink>
    static void write_tuple(Sink& sink, std::tuple<Types...> const& value, index<0>)
    {
        write(sink, std::get<0>(value));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_pair_hpp
