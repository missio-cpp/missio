//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_asio_ip_endpoint_hpp
#define _missio_format_adapters_boost_asio_ip_endpoint_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/asio/ip/basic_endpoint.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename InternetProtocol>
struct type_adapter<boost::asio::ip::basic_endpoint<InternetProtocol>>
{
    template <typename Sink>
    static void format(Sink& sink, boost::asio::ip::basic_endpoint<InternetProtocol> const& value)
    {
        if(is_v4_endpoint(value))
            write(sink, value.address(), ':', value.port());
        else
            write(sink, '[', value.address(), ']', ':', value.port());
    }

    static bool is_v4_endpoint(boost::asio::ip::basic_endpoint<InternetProtocol> const& value)
    {
        return value.protocol() == InternetProtocol::v4();
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_asio_ip_endpoint_hpp
