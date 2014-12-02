//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_shared_ptr_hpp
#define _missio_format_adapters_std_shared_ptr_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <memory>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value>
struct type_adapter<std::shared_ptr<Value>>
{
    template <typename Sink>
    static void format(Sink& sink, std::shared_ptr<Value> const& value)
    {
        if(value)
            write(sink, *value);
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_shared_ptr_hpp
