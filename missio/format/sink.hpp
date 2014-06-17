//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_sink_hpp
#define _missio_format_sink_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_buffer.hpp>


namespace missio
{
namespace format
{

typedef detail::sink_buffer sink;

}   // namespace format
}   // namespace missio

#endif  // _missio_format_sink_hpp
