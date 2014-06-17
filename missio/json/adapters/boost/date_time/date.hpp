//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_adapters_boost_date_time_date_hpp
#define _missio_json_adapters_boost_date_time_date_hpp

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
struct adapt<boost::gregorian::date>
{
    typedef string type;

    static string to(boost::gregorian::date const& value)
    {
        return string(boost::gregorian::to_iso_extended_string(value));
    }

    static boost::gregorian::date from(string const& value)
    {
        return boost::gregorian::from_simple_string(value);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_adapters_boost_date_time_date_hpp
