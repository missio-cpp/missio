//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_system_error_code_hpp
#define _missio_format_adapters_boost_system_error_code_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/system/error_code.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::system::error_code>
{
    template <typename Sink>
    static void format(Sink& sink, boost::system::error_code const& value)
    {
        write(sink, value.category().name(), ':', value.value());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_system_error_code_hpp