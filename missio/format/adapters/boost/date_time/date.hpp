//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_date_time_date_hpp
#define _missio_format_adapters_boost_date_time_date_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/inserters_impl.hpp>

// BOOST headers
#include <boost/date_time.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::gregorian::date>
{
    template <typename Sink>
    static void format(Sink& sink, boost::gregorian::date const& value)
    {
        write(sink, dec(year(value), 4), '-', month(value), '-', dec(day(value), 2));
    }

    static char const* month(boost::gregorian::date const& value)
    {
        return value.month().as_short_string();
    }

    static unsigned short day(boost::gregorian::date const& value)
    {
        return static_cast<unsigned short>(value.day());
    }

    static unsigned short year(boost::gregorian::date const& value)
    {
        return static_cast<unsigned short>(value.year());
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_date_time_date_hpp
