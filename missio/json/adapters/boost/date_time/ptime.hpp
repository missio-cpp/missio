//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_adapters_boost_date_time_ptime_hpp
#define _missio_json_adapters_boost_date_time_ptime_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/date_time.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <>
struct adapt<boost::posix_time::ptime>
{
    typedef string type;

    static string to(boost::posix_time::ptime const& value)
    {
        return string(boost::posix_time::to_iso_extended_string(value));
    }

    static boost::posix_time::ptime from(string const& value)
    {
        // There is no from_iso_extended_string function in Boost.DateTime
        return boost::date_time::parse_delimited_time<boost::posix_time::ptime>(value, 'T');
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_adapters_boost_date_time_ptime_hpp
