//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_item_hpp
#define _missio_format_detail_format_item_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/utility/string_ref.hpp>
#include <boost/cstdint.hpp>


namespace missio
{
namespace format
{
namespace detail
{

struct format_item
{
    boost::uint32_t index;
    boost::string_ref string;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_item_hpp
