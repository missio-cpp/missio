//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_asio_ip_address_hpp
#define _missio_format_adapters_boost_asio_ip_address_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/asio/ip/address.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::asio::ip::address>
{
    template <typename Sink>
    static void format(Sink& sink, boost::asio::ip::address const& value)
    {
        write(sink, value.to_string());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_asio_ip_address_hpp
