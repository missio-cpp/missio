//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_adapters_boost_filesystem_path_hpp
#define _missio_json_adapters_boost_filesystem_path_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/filesystem/path.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <>
struct adapt<boost::filesystem::path>
{
    typedef string type;

    static string to(boost::filesystem::path const& value)
    {
        return string(value.native());
    }

    static boost::filesystem::path from(string const& value)
    {
        return boost::filesystem::path(value);
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_adapters_boost_filesystem_path_hpp
