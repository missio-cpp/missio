//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_item_hpp
#define _missio_format_detail_format_item_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers headers
#include <missio/format/detail/string_view.hpp>

// STL headers
#include <cstdint>


namespace missio
{
namespace format
{
namespace detail
{

struct format_item
{
    std::uint32_t index;
    string_view string;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_item_hpp
