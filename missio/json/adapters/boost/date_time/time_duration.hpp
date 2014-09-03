//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_adapters_boost_date_time_time_duration_hpp
#define _missio_json_adapters_boost_date_time_time_duration_hpp

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
struct adapt<boost::posix_time::time_duration>
{
    typedef string type;

    static string to(boost::posix_time::time_duration const& value)
    {
        return string(boost::posix_time::to_simple_string(value));
    }

    static boost::posix_time::time_duration from(string const& value)
    {
        return boost::posix_time::duration_from_string(value);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_adapters_boost_date_time_time_duration_hpp
