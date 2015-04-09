//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_filesystem_path_hpp
#define _missio_format_adapters_boost_filesystem_path_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/filesystem/path.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<boost::filesystem::path>
{
    template <typename Sink>
    static void format(Sink& sink, boost::filesystem::path const& value)
    {
        write(sink, '"', value.string(), '"');
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_filesystem_path_hpp
