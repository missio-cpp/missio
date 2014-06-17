//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_smart_ptr_intrusive_ptr_hpp
#define _missio_format_adapters_boost_smart_ptr_intrusive_ptr_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/intrusive_ptr.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value>
struct type_adapter<boost::intrusive_ptr<Value>>
{
    template <typename Sink>
    static void format(Sink& sink, boost::intrusive_ptr<Value> const& value)
    {
        if(value)
            write(sink, *value);
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_smart_ptr_intrusive_ptr_hpp
