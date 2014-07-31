//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_exception_hpp
#define _missio_format_adapters_std_exception_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <type_traits>
#include <exception>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value>
struct type_adapter<Value, typename std::enable_if<std::is_base_of<std::exception, Value>::value>::type>
{
    template <typename Sink>
    static void format(Sink& sink, Value const& value)
    {
        write(sink, value.what());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_exception_hpp
