//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_adapters_boost_uuid_uuid_hpp
#define _missio_json_adapters_boost_uuid_uuid_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <>
struct adapt<boost::uuids::uuid>
{
    typedef string type;

    static string to(boost::uuids::uuid const& value)
    {
        return string(boost::uuids::to_string(value));
    }

    static boost::uuids::uuid from(string const& value)
    {
        return boost::uuids::string_generator()(std::string(value));
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_adapters_boost_uuid_uuid_hpp
