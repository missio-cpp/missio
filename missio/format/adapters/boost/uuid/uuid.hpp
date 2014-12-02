//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_uuid_uuid_hpp
#define _missio_format_adapters_boost_uuid_uuid_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/uuid/uuid_io.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::uuids::uuid>
{
    template <typename Sink>
    static void format(Sink& sink, boost::uuids::uuid const& value)
    {
        write(sink, boost::uuids::to_string(value));
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_uuid_uuid_hpp
