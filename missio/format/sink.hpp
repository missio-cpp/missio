//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_sink_hpp
#define _missio_format_sink_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// Application headers
#include <missio/format/detail/sink_buffer.hpp>


namespace missio
{
namespace format
{

using sink = detail::sink_buffer;

}   // namespace format
}   // namespace missio

#endif  // _missio_format_sink_hpp
