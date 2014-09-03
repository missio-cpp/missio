//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_adapters_boost_asio_ip_address_hpp
#define _missio_json_adapters_boost_asio_ip_address_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/asio/ip/address.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <>
struct adapt<boost::asio::ip::address>
{
    typedef string type;

    static string to(boost::asio::ip::address const& value)
    {
        return string(value.to_string());
    }

    static boost::asio::ip::address from(string const& value)
    {
        return boost::asio::ip::address::from_string(value);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_adapters_boost_asio_ip_address_hpp
